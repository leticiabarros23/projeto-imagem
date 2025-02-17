#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

int main()
{
    stdio_init_all();   // Inicializa os tipos stdio padrão presentes ligados ao binário

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

restart:

// Parte do código para exibir a mensagem no display (opcional: mudar ssd1306_height para 32 em ssd1306_i2c.h)
// /**
    char *text[] = {
        "  Bem-vindos!   ",
        "  Embarcatech   "};

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);
// */

// Parte do código para exibir a linha no display (algoritmo de Bresenham)
/**
    ssd1306_draw_line(ssd, 10, 10, 100, 50, true);
    render_on_display(ssd, &frame_area);
*/

// Parte do código para exibir o bitmap no display

    const uint8_t bitmap_128x64[] = { 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x1f, 0xfc, 0xbf, 0xff, 0xff, 
	0xff, 0xff, 0xf9, 0x1f, 0xf8, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xcf, 0xff, 0xff, 
	0xff, 0xff, 0xc3, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xc1, 0xff, 0xff, 
	0xff, 0xff, 0x03, 0x1f, 0xf8, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x0f, 0xf0, 0xe0, 0xff, 0xff, 
	0xff, 0xff, 0x87, 0x03, 0xc0, 0xe1, 0xff, 0xff, 0xff, 0xff, 0x87, 0x03, 0xc0, 0xe1, 0xff, 0xff, 
	0xff, 0xff, 0xc7, 0x01, 0x80, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x00, 0x00, 0xf3, 0xff, 0xff, 
	0xff, 0xff, 0xef, 0x00, 0x00, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x6f, 0x00, 0x00, 0xf6, 0xff, 0xff, 
	0xff, 0xff, 0x7f, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xfc, 0xff, 0xff, 
	0xff, 0xff, 0x3f, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xfc, 0xff, 0xff, 
	0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 
	0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 
	0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 
	0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x0d, 0x00, 0x00, 0xb0, 0xff, 0xff, 
	0xff, 0xff, 0x0c, 0x00, 0x00, 0x30, 0xff, 0xff, 0xff, 0x3f, 0x0c, 0x00, 0x00, 0x30, 0xfc, 0xff, 
	0xff, 0x1f, 0x0c, 0x00, 0x00, 0x30, 0xf8, 0xff, 0xff, 0x07, 0x0c, 0x00, 0x00, 0x30, 0xe0, 0xff, 
	0xff, 0x07, 0x0c, 0x00, 0x00, 0x30, 0xe0, 0xff, 0xff, 0x0f, 0x0c, 0x00, 0x00, 0x30, 0xf0, 0xff, 
	0xff, 0x3f, 0x0c, 0x00, 0x00, 0x30, 0xfc, 0xff, 0xff, 0x7f, 0x0c, 0x00, 0x00, 0x30, 0xfe, 0xff, 
	0xff, 0xff, 0x0d, 0x00, 0x00, 0xb0, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 
	0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 
	0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 
	0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 
	0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xfc, 0xff, 0xff, 
	0xff, 0xff, 0x3f, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xfe, 0xff, 0xff, 
	0xff, 0xff, 0x6f, 0x00, 0x00, 0xf6, 0xff, 0xff, 0xff, 0xff, 0x6f, 0x00, 0x00, 0xf6, 0xff, 0xff, 
	0xff, 0xff, 0xcf, 0x00, 0x00, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x01, 0x80, 0xe3, 0xff, 0xff, 
	0xff, 0xff, 0x87, 0x01, 0x80, 0xe1, 0xff, 0xff, 0xff, 0xff, 0x87, 0x03, 0xc0, 0xe1, 0xff, 0xff, 
	0xff, 0xff, 0x07, 0x07, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x1f, 0xf8, 0xc0, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xc3, 0xff, 0xff, 
	0xff, 0xff, 0xe3, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x9f, 0xf9, 0x8f, 0xff, 0xff, 
	0xff, 0xff, 0xf9, 0x1f, 0xf8, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
   
    };

    ssd1306_t ssd_bm;
    ssd1306_init_bm(&ssd_bm, 128, 64, false, 0x3C, i2c1);
    ssd1306_config(&ssd_bm);

    ssd1306_draw_bitmap(&ssd_bm, bitmap_128x64);
*/

    while(true) {
        sleep_ms(1000);
    }

    return 0;
}

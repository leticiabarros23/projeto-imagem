### **Documentação - Exibição de Imagem no Display OLED SSD1306**  

#### **Introdução**  
Este programa tem como objetivo exibir uma imagem no display OLED SSD1306 utilizando comunicação I2C na placa Raspberry Pi Pico. Através do protocolo I2C, o programa inicializa o display, configura os pinos adequados e renderiza um bitmap de 128x64 pixels na tela.  

#### **Funcionamento do Código**  

##### **Inicialização do sistema:**  
- Configura os pinos de comunicação **SDA (14)** e **SCL (15)** para I2C.  
- Inicializa a comunicação I2C com o display OLED.  
- Configura o display para exibição da imagem.  

##### **Exibição da Imagem:**  
- Um **bitmap pré-definido** (array de bytes) é carregado no buffer do display.  
- A função **ssd1306_draw_bitmap** exibe a imagem no OLED.  

##### **Loop infinito:**  
- O programa entra em um loop que mantém a imagem na tela indefinidamente.  

#### **Hardware Utilizado**  
- **Raspberry Pi Pico** (placa de desenvolvimento)  
- **Display OLED SSD1306** (resolução 128x64 pixels, comunicação via I2C)  
- **Fios de conexão** (*jumper wires*) para ligar os pinos corretamente.  

#### **Bibliotecas Utilizadas**  
- **pico/stdlib.h**: Biblioteca padrão da Raspberry Pi Pico.  
- **hardware/i2c.h**: Biblioteca para comunicação I2C.  
- **ssd1306.h**: Biblioteca para controle do display OLED.  

#### **Conclusão**  
Este programa demonstra como inicializar um display OLED SSD1306 em uma Raspberry Pi Pico e exibir uma imagem estática. **Pretende-se expandir para** exibição de mensagens dinâmicas, gráficos ou outras interações conforme necessário.  



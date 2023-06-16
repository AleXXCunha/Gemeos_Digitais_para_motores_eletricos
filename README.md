# Gêmeos Digitais para Motores Elétricos
Trabalho de Graduação desenvolvido para a obtenção do diploma de Engenheiro Mecatrônico da Universidade de Brasília (UnB), no qual consiste na construção de um Gêmeo Digital para motores elétricos. Os arquivos aqui presentes são os códigos para a IDE do Arduino, utilizados para a leitura dos dados dos sensores conectados a um microcontrolador, e os dados do projeto desenvolvido no ScadaBR, o sistema supervisório responsável por monitorar as variáveis tanto dos sensores quanto do inversor de frequência CFW-08 que realiza o acionamento/controle de velocidade e torque do motor.

## Leitura de Dados
Apesar do inversor de frequência conseguir disponibilizar diversas informações dos motores, existem outros dados que não são possíveis de serem obtidos por meio dele. Por isso, definiu-se controladores e atuadores para capturar estes valores. Entretanto, primeiramente, era necessário definir quais informações além das que o inversor fornece seriam necessárias para a construção do modelo virtual de um motor. Chegou-se à conclusão de que 3 informações importantes para a modelagem do motor estavam faltando, sendo elas a temperatura externa da carcaça, o ruído emitido pelo motor e a vibração nos 3 eixos.

O microcontrolador utilizado neste trabalho foi o ESP32, juntamente com o sensor de temperatura DS18B20, o módulo sensor de som KY-038 e o acelerômetro MPU-6050. O código arduino aqui disposto usa as bibliotecas **_modbus-esp8266_**, **_Adafruit_MPU6050_**, **_Adafruit_Sensor_** e **_DS18B20_**. Portanto, você precisará instalá-los usando o Library Manager no Arduino IDE ou baixar a versão mais recente do GitHub. Porteriormente, para funcionar o código basta conectar o ESP32 juntamente com os sensores ao computador via cabo USB, compilar e executar.

A conexão entre o ESP32 e os sensores segue conforme mostrado no diagrama esquemático a seguir:

![esquematico_bb](https://github.com/AleXXCunha/Gemeos_Digitais_para_motores_eletricos/assets/66271454/97c0afec-6266-4fda-88be-6918051ce8bd)

## ScadaBR
De forma a facilitar o acesso às informação obtidas pelo inversor e pelos sensores, também foi desenvolvido um sistema SCADA para a monitoração dos dados, implementando no processo alguns recursos úteis como registro de eventos, alarmes e gráficos. Os dados deste sistema se encontram na pasta _ScadaBR_, que é o software utilizado para isso. Com o ScadaBR instalado em outra máquina ou servidor, é possível importar estes dados colando o código JSON no campo de dados e clicando em “importar”. Também é necessário substituir a pasta _Uploads_ pela existente na máquina.

Este processo de transferência é executado desta maneira visto que o recurso de exportação em .ZIP não está funcionando nas versões 1.1 e 1.2 do ScadaBR. Para fazer uma exportação completa é necessário fazer backup dos dados utilizando a ferramenta de exportar/importar JSON e copiar manualmente os arquivos das pastas Uploads e Graphics. A pasta Uploads é a pasta do ScadaBR que contém os dados que foram enviados pelo usuário ao sistema, como as figuras de fundo das representações gráficas, por exemplo. Já a pasta Graphics é a pasta que contém as figuras utilizadas nas representações gráficas. Estas pastas se encontram nos seguintes diretórios:

_<Pasta de instalação do Tomcat>/webapps/ScadaBR/uploads_  
_<Pasta de instalação do Tomcat>/webapps/ScadaBR/graphics_

No Windows, a pasta de instalação do Tomcat costuma ser (para o ScadaBR 1.2):  
_C:\Program Files\ScadaBR\tomcat_ ou  
_C:\Program Files (x86)\ScadaBR\tomcat_

No Linux, a pasta de instalação do Tomcat costuma ser (para o ScadaBR 1.2):  
_/opt/ScadaBR/tomcat/_

Em relação à pasta Graphics, somente é necessário copiar os arquivos dela caso o usuário tenha incluído manualmente novos componentes gráficos no sistema, o que não é o caso deste trabalho. Por isso esta respectiva pasta não se encontra dentre os arquivos deste repositório.

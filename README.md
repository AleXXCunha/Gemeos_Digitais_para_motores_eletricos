# Gemeos_Digitais_para_motores_eletricos
Trabalho de Graduação desenvolvido para a obtenção do diploma de Engenheiro Mecatrônico da UnB, no qual consiste na construção de um Gêmeo Digital para motores elétricos. Os arquivos aqui presentes são os códigos para a IDE do Arduino, utilizados para a leitura dos dados dos sensores conectados a um microcontrolador, e códigos e imagens do ScadaBR utilizados para o desenvolvimento do sistema supervisório, responsável por monitorar os dados tanto dos sensores quanto do inversor de frequência que realiza o acionamento/controle de velocidade e torque do motor.

O recurso de exportação em .ZIP não está funcionando nas versões 1.1 e 1.2 do ScadaBR. Para fazer uma exportação completa é necessário fazer backup dos dados utilizando a ferramenta de exportar/importar JSON e copiar manualmente os arquivos das pastas Uploads e Graphics. A pasta Uploads é a pasta do ScadaBR que contém os dados que foram enviados pelo usuário ao sistema, como as figuras de fundo das representações gráficas, por exemplo. Já a pasta Graphics é a pasta que contém as figuras utilizadas nas representações gráficas. Estas pastas se encontram nos seguintes diretórios:

_<Pasta de instalação do Tomcat>/webapps/ScadaBR/uploads_
_<Pasta de instalação do Tomcat>/webapps/ScadaBR/graphics_

No Windows, a pasta de instalação do Tomcat costuma ser (para o ScadaBR 1.2):
_C:\Program Files\ScadaBR\tomcat_ ou
_C:\Program Files (x86)\ScadaBR\tomcat_

No Linux, a pasta de instalação do Tomcat costuma ser (para o ScadaBR 1.2):
_/opt/ScadaBR/tomcat/_

Em relação à pasta Graphics, somente é necessário copiar os arquivos dela caso o usuário tenha incluído manualmente novos componentes gráficos no sistema, o que não é o caso deste trabalho. Por isso esta respectiva pasta não se encontra dentre os arquivos deste repositório.

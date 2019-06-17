# IO-Extended-Aracaju-Presentation
Implementando Sua Primeira Solução De IOT Usando Firebase

## Sobre
Neste repositório estão o código fonte e configurações de projeto usados, além disso algumas informações extras e slide de apresentação. O objetivo é capturar a temperatura ambiente e enviar para uma database de tempo real no Firebase.

## Materiais usados
- Protoboard
- NodeMCU (ESP8266)
- NTC50D - 11 (Termistor)
- Dois resistores de 100 ohms (Resistores comuns de 1/4)

## Circuito
![Circuito](https://github.com/ThiagoFontes/IO-Extended-Aracaju-Presentation/raw/master/circuito.png)

## Compilando e envianado código para a placa
Recomendo a utilização do Atom instalando todas as extensões do Platform.io. Após clonar o projeto e abrir a pasta  **firebase-sensor** no editor, com a opção **File -> Add Project Folder** é preciso informar no arquivo **main.cpp**:
- Nome da rede wifi que será utilizada
- Senha da rede wifi
- URL para o seu projeto firebase
- Chave secreta do banco de dados

### Bibliotecas usadas
- Firebase ESP8266 Client by Mobizt
- universal-thermistor by Paul Cowan

Após as modificações no código, para compilar usar a opção **build**, para enviar o código para a placa que deve estar conectada via USB e já com o circuito montado usar a opção **upload**.

# Dokumentácia 

## Úvod
názov:   Klient pre vzdialenú kalkulačku
autor:   Matúš Hubinský
xlogin:  xhubin04
dátum:   21.03.2023
predmet: IPK

## Teória

### IP adresa
štyri osmice bytov ktoré identifikuje a dresuje sieťové rozhranie pripojené k počítačovej sieti. Aktuálne sa používajú dva varianty, IPv4 a IPv6. IPv4 je 32 bitové číslo, definované ako štyri osmice bytov napr.: `192.168.42.42`. Vyhradená IP adressa `127.0.0.1` slúži pre localhost, t.j. používané zariadenie.

### Port
Kladné celé číslo od 0 do 65535. Identifikuje špecifický proces alebo sieťovú službu. Port je na softvérovej úrovni a identifikuje každý sieťový protokol a IP adresu.
Rozdeľujú sa na tri skupiny:
1. Známe porty: od 0 do 1023
2. Registrované porty: od 1024 do 49151
3. Dynamické porty: od 49152 do 65535

### Transportný protokol 
Popisuje pravidlá ktorými budú dvaja alebo viacerý aktéri sieťového spojenia spolu kominukovať. Poznáme dva hlavné: UDP a TCP. 

#### UDP (User Datagram Protocol)
Tento protokol nevyžaduje predošlú inicializáciu komunikácie. Nastávajú problémy ako strata paketov po ceste, duplikovanie paketov alebo strata poradia, preto sa povaźuje za nespoľahlivý. Pre svoju jednoduchosť sa používa pri zasielaní obsahu viacerým klientom (napr. video streaming). Komunikácia medzi klientom a serverom nieje inicializovaná.

#### TCP (Transmission Control Protocol)
Tento komunikačný protokol poskytuje spoľahlivý, usporiadaný a kontrolovaný prenos dát. Komunikácia medzi klientom a serverom musí byť inicializovaná zo strany klienta. Po inicializovaní môže byť ukončená serverom alebo klientom správou [FIN].
[SYN]:     Klient pošle správu [SYN] server na začiatku komunikácie
[SYN-ACK]: Odpoveď serveru na klientovu správu [SYN]
[ACK]:     Klient pošle serveru naspať odpoveď [ACK], čím potvrdí nadviazenie komunikácie

### Socket address
socket address je trojica skladajúca sa z:
1. Trasportného protokolu
2. IP adressy
3. Čísla portu 

## Základný popis funkcionality programu
Program dostane na vstup IP adressu, číslo portu a typ komunikačného protokolu, "TCP" alebo "UDP". Ako prvý krok si vyberie typ komunikácia so serverom. Potom si vytvotý "socket", čize kanál cez ktorý bude so serverom komunikovať. Socket vytvorý na základe parametrov zadaných na vstupe. Ak sa socket nepodarilo vytvoriť, program končí chybou. Pokiaľ sa so serverom podarí nadviazať komunikáciu, program beží dokedy ho užívateľ nevypne alebo nenastane chyba, ktorá by vyžadovala ukončenie komunikácie so serverom. Ak server neopodvedá viac ako 2 sekundy, komunikácia so serverom je ukončená.

## Testovanie
Základné testovanie pomocou vlastného bash scriptu `test.sh`. 

Testovanie na serveri:
<screeenshot>

Testovanie pomocou vlastneho servera:
<screeenshot>

## Extra funkcionality
- TODO: doxygen

## Bibliografia
referencia 

Vladimir Vesely DemoTcp [online]. Publisher: Brno University of Technology, Faculty of Information Technology, January 30th 2023. [cit. 2023-03-02]. Available at: https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Stubs/cpp/DemoTcp. 


[1] https://man7.org/linux/man-pages/
[2] https://www.gnu.org/licenses/gpl-3.0.en.html
[3] https://stackoverflow.com/questions/8666378/detect-windows-or-linux-in-c-c
[4] https://stackoverflow.com/questions/315948/c-catching-all-exceptions
[5] https://en.wikipedia.org/wiki/User_Datagram_Protocol
[6] https://en.wikipedia.org/wiki/Transmission_Control_Protocol
[7] https://en.wikipedia.org/wiki/IP_address
[8] https://en.wikipedia.org/wiki/Localhost
[9] https://en.wikipedia.org/wiki/Port_(computer_networking)
[10] https://en.wikipedia.org/wiki/Network_socket


https://stackoverflow.com/questions/1641182/how-can-i-catch-a-ctrl-c-event
# Bluetooth Smart Car

Autore: Manuel Savà

Descrizione: il progetto consiste nella realizzazione di una macchinina comandabile via Bluetooth da qualsiasi Device compatibile con modulo Bluetooth HC-06. La Smart car presenta due modalità di utlizzo, switchabili in qualsiasi istante dal device collegato: La prima denominata "guida libera", selezionata di default all'accensione, consiste nel comandare la macchinina tramite il pad virtuale del device, decidendo liberamente la velocità di movimento e la direzione da farle prendere, mentre la seconda consiste in una sorta di "pilota automatico", facendola muovere autonomamente e fermandosi una volta al cospetto di un qualsiasi ostacolo, cambiando successivamente direzione verso la via più libera. La funzionalità del fermarsi dinanzi a un ostacolo è presente anche nella guida libera, ma in questo caso la Smart Car si limiterà solo a stoppare i motori, lasciando pieno controllo all'utente su quale strada percorrere.  

# Hardware e materiale utilizzato:

- Aruino uno
- Modulo Bluetooth HC-06
- DC Motor Shield L293D
- 2 Batterie 18650 da 3.7V
- Porta Batterie con Switcher integrato
- Sensore a ultrasuoni HC-SR04
- 4 Motori DC con ruote annesse
- Chassis a 2 strati in plastica

# Librerie utilizzate:

- Servo
- SoftwareSerial
- AFMotor
- NewPing

# Limitazioni del Progetto

- La presenza di un solo sensore ad ultrasuoni permette solo di vedere gli ostacoli posizionati davanti alla Smart Car.

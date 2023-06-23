# TiMiNoo
Cute 1 bit VPet for Arduino - Feed, cuddle, clean and educate your own unique cat.

2 mini games, 7 food types, friends visits and presents, one button action, no sound, no death.

![TiMiNoo logo](./assets/logo/2.png "TiMiNoo logo")

## Current version: 1.2.8
## WIP version: n/a

## Presentation

TiMiNoo ("Tee Me Noo") is a virtual cat providing minimal distraction, fully office-compatible, single button action, no sound, no death.
The cat is different on each run, its characteristics (appetite, cleanliness, cleverness, playfulness) are randomly picked at startup.

TiMiNoo has been created with busy people in mind: The gameplay is very simple and fluid on purpose, as this game is meant to be enjoyed in a work environment.

TiMiNoo is a simple yet feature-rich virtual cat, a companion for busy days: Cuddle, Feed, Educate, Wash and Entertain your very own furry companion.

Tamagotchi lovers could compare it to a Nano.

## Features
### Single button gameplay
I love having a virtual pet on my desk at work, but I also need to preserve my workflow from distractions.
A single button gameplay is perfect for that.
### 2 mini games
#### Catsino ![bar](./assets/icons/bar.png "BAR +1 of all !!!")
Go to the casino with your TiMiNoo and do your best to win some yummy food to bring home.
Press the button once to randomly pick a food item. Beware of the ghost though !
#### Cat Wash
When the fur of your TiMiNoo gets dirty, it's time for a proper toilet. Scrub scrub !
Repeatedly press the button to get a squicky clean kitty.
### 7 food items
Your TiMiNoo will get hungry as time goes by. Feed it a variety of food including:
- ![grape](./assets/icons/grape.png "Fresh grapes") Grape
- ![strawberry](./assets/icons/strawberry.png "Yummy strawberry") Strawberry
- ![apple](./assets/icons/apple.png "Tasty apple") Apple
- ![orange](./assets/icons/orange.png "Juicy orange") Orange
- ![milk](./assets/icons/milk.png "Farm milk") Milk
- ![cake](./assets/icons/coco_cake.png "Homemade coco cake") Coco cake (bonus item)
- ![matcha](./assets/icons/matcha.png "Matcha tea") Matcha tea (bonus item)
### Educate your cat with Professor Koko ![koko](./assets/icons/koko_le_snail.png "Koko Le Snail")
Your TiMiNoo will want to learn new things. Call Professor Koko Le Snail, a wise teacher that will share is best knowledge with your cuttie.
### Cuddle
TiMiNoo craves attention and love, make sure to give it plenty.
### Random visits from a friend ![cindy](./assets/icons/cindy.png "Your friend")
Sometimes, when the cat gets hungry, its friend will come and offer either a nice Matcha tea or a home made Coco cake.
### Scoring system
Earn points every time you take action and increase your score.
#### Feed
- Strawberry: +30 points
- Grape, orange, apple: +20 points
- Milk: +10 points
#### Play
- BAR: +500 points
- Strawberry: +300 points
- Grape, orange, apple: +200 points
- Milk: +100 points
#### Cuddle
- Give a big kiss and a hug to your cat: +50 points
#### Educate
- Get some good wisdom from Koko Le Snail: +100 points
#### Wash
- Keep your cat clean: +200 points
#### Visit from a friend
- Receive a visit from your friend: +10000 points
#### Beware of the ghost !
- Ghost encounter: -666 points

## How to play
### Starting the game
Plug your TiMiNoo to a 5V Micro USB charger, a new game will start.
There is no save feature, no scoring, no experience. Every run is a fresh beginning with new statistics.
TiMiNoo cannot die.
### Understand what your TiMiNoo wants
#### Home screen
TiMiNoo looks straight at you, waving its tail.
It's happy, simply enjoying the moment.
#### TiMiNoo wants to play
![play](./assets/icons/play.png "Play")
The cat will look at a gamepad icon.
Press the button once to play the integrated game: Casino.
Food items will appear on the screen, press the button once to try your luck and see what you catch.
That game is how TiMiNoo gets new food into its pantry.
#### TiMiNoo wants to go to school
![educate](./assets/icons/study.png "Study")
The cat will look at a book icon.
Press the button once to call Professor Koko Le Snail, a wise and knowledgeable teacher. He will happily share his best quotes with your TiMiNoo.
#### TiMiNoo is hungry
![feed](./assets/icons/pizza.png "Feed")
The cat will look at a pizza slice icon.
Press the button to feed your TiMiNoo with the food stashed in the pantry. 
#### TiMiNoo wants to cuddle with you
![cuddle](./assets/icons/cuddle.png "Cuddle")
The cat will look at a half-empty heart icon.
Press the button to kiss your furry cuttie.
#### TiMiNoo needs a bath
![clean](./assets/icons/bubbles.png "Clean")
The cat will look at a bubble icon.
Press the button in order to scrub all that dust off its fur.
## How to build your own

![Prototype board](./assets/proto5.jpg "TiMiNoo")

### Items
- 1x Arduino Leonardo R3
- 1x Button
- 1x 128*64 OLED screen
- 1x 10k Ohm resistor
- 1x breadboard or prototyping board
- 1x Acrylic enclosure for UNO / Leonardo
- Enough jumper cables to assemble the circuitry
### Assembly
![Circuit top](./assets/timinoo_circuit_top.jpg "TiMiNoo circuit top")
![Circuit bottom](./assets/timinoo_circuit_bottom.jpg "TiMiNoo circuit bottom")
![Circuit](./assets/timinoo_circuit.jpg "TiMiNoo circuit")
#### Screen pinout
- DC -> D9
- CS -> D10
- MOSI -> D11
- CLOCK -> D13
- RES -> RST
- VCC -> 5V
- GND -> GND
#### Button
- GND -> GND
- VCC -> 3V
- SIG -> D2
### Installation instructions
Use [Arduino IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE) to upload `timinoo.ino` to your Arduino Leonardo.
Make sure you use a Micro USB cable that supports data transfer, as some cables do not have data lines wired and only provide charging capability.

## Commercial status
TiMiNoo is an open source project that is not meant to be sold. Please note the cat sprites and the frames are under a [Creative Commons Attribution-NonCommercial 4.0 International CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) license that explicitly prohibits commercial use. I'm 100% OK with this.

# Meteolienne-V2

A project aiming to create an extra-efficient wind turbine, that's able to spin around to face the wind, and includes several sensors to add weather station capabilities.

It's also capable of generating up to 10W of power, and is entirely self-sufficient, thanks to an on-board battery and solar panel, and a sleeping system to save power.

Here are some pictures:  
![View from the bottom](https://github.com/Uiop3385/Meteolienne-V2/blob/55d44287617ceda9696ecf1af9f7fe702a5b29cc/pictures/outside_low.jpg)

![View from the top](https://github.com/Uiop3385/Meteolienne-V2/blob/55d44287617ceda9696ecf1af9f7fe702a5b29cc/pictures/outside_high.jpg)

## Disclaimer
If you're going to use any part of this project, please make sure you follow the terms of the licence. You can see a breakdown of them [here](https://choosealicense.com/licenses/mpl-2.0/).

## Info

This project is the successor to the [original Météolienne](https://github.com/Uiop3385/Meteolienne-V1) I've made. Compared to the first one:

- It's actually *somewhat* finished
- It communicates using WiFi and can be controlled through an app and web dashboard
- It implements the weather station capabilities
- It's far more energy efficient
- It generates power

The wireless connection is operated through Arduino IoT Cloud, using an Arduino MKR WiFi 1010 board. You'll need an account and a Maker subscription to make it work.

Some parts of this project, including variables in the code, part names in the CAD representation, etc, **are written in French**.

## Dashboards
Here are two images showcasing part of the two dashboards, the data one first, and the settings one after.

![Data dashboard](https://github.com/Uiop3385/Meteolienne-V2/blob/55d44287617ceda9696ecf1af9f7fe702a5b29cc/pictures/data-dashboard.png)

![Settings dashboard](https://github.com/Uiop3385/Meteolienne-V2/blob/55d44287617ceda9696ecf1af9f7fe702a5b29cc/pictures/settings-dashboard.png)

These are the web dashboards. The mobile versions of them aren't shown here, but they're the same with a different layout to fit the size of a phone screen.

## Scripts
The files included in /scripts are not ready for use on the IoT Cloud editor. If you want to implement the code, dashboard, things and cloud variables, it's essential to use the template. If you're simply taking certain parts of the scripts, ignore this.

### Guide:
- Download meteolienne_template.tino in /scripts
- Access the Cloud Dashboard (https://app.arduino.cc)
- Go to Templates, then click on "Your Templates" at the top
- Select "Import local template (.tino)"
- Import the file you downloaded
- Then, press "Use template"
- You'll be asked to connect an Arduino MKR WiFi 1010

Once this is done, everything will automatically be copied over, and you're almost ready to upload! Just fill in the secrets tab with your WiFi credentials, and your ipdata API key for geolocation (you can get one free from their website, https://ipdata.co).

## Models
The entire wind turbine was modelled using Autodesk Fusion. You can access the .f3z from /models. If you're using a different CAD, there's also a .step you can use.

Alternatively, all parts of the wind turbine are available as .stl in /models/parts.

Render of the turbine from Fusion:
![Realistic render of the wind turbine](https://github.com/Uiop3385/Meteolienne-V2/blob/55d44287617ceda9696ecf1af9f7fe702a5b29cc/pictures/render.png)

The models were designed to be 3D printed. The ideal materials would be PETG and ASA, since they're strong, water resistant, and UV resistant. My prototype was made using PETG, with white filament for all parts but the mast cover and the IO shield. Those were printed in translucent filament.

## Components used
### Sensors
|Part name|Brand|Qty|
|--|--|--|
|MQ135 Air Quality sensor|Flying Fish|1|
|SEN0501 Environmental Sensor|DFRobot|1|
|NVGRLEX002 Wind vane + board|Lextronic|1|

### Other components
|Part name|Brand|Qty|
|--|--|--|
|C6045 Voltage Generator|cebekit|1|
|MKR WiFi 1010 board|Arduino|1|
|mBot Battery (Li-Po, 3.7V, 1800mAh)|Makeblock|1|
|28BYJ-48 Stepper Motor + Driver|N/A|1|
|S7V8F5 5V Voltage Regulator|Polulu|1|
|313070000 2.5W Solar Panel|Seeed Studio|1|

### Electronic components
|Type|Value/Ref|Qty|
|--|--|--|
|Resistor|220Ω|2|
|Resistor|1kΩ|4|
|Resistor|10kΩ|4|
|Resistor|15kΩ|2|
|Pushbutton|N/A|1|
|Capacitor|1000µF|1|
|LED|N/A|1|
|Diode|1N4007|6|
|Transistor|2N2222|4|

### Assembly parts:
|Type|ISO Reference|Value|Qty
|--|--|--|--|
|Bolt|ISO 4017|M4x10|19
|Nut|ISO 4035|M4|19|
|Screw|ISO 7046|M4x40|1|

And a bunch of jumper wires.

Image of the inside:![Inner wiring](https://github.com/Uiop3385/Meteolienne-V2/blob/2a13d240635c14f368a44f7f5a6f722d9530c754/pictures/inside.png)

## Oversights
While the project seems finished, there's still many things that are wrong with it. Here's a quick list of them:
- I can't actually get it to work. I'm unsure if the problem comes from my program or my board, but it won't let me upload it. The board no longer shows up on the computer outside of bootloader mode.
- Many components used rely on 5V, which I unsuspectingly hooked up to the 5V pin. However, this pin only outputs the 5V power coming from the USB. That means the board will never output this voltage from battery. The turbine is therefore not "self-sufficient".
- The wind near the ground is highly unstable. If you were to place the turbine on the ground, it would greatly struggle to pick up wind correctly. Not to mention, the wind vane would act very strangely too. It would need to be suspended much higher into the air for everything to function correctly.
- If wind speeds get too high, there's no protection to prevent the blades from spinning too fast and damaging the internals.
- There are several design flaws in my model. I only noticed them when assembling the turbine, and haven't fixed them since.
- Geolocation is, by design, highly inaccurate, since it's basing itself on IP address location. During testing, I could only ever get it to locate me in the same place in Germany (probably the location of the IoT Cloud servers). This could be mitigated by using Google's API.

## Assembly
I will not be providing any assembly instructions. You'll have to do with the information available here. Who would even want to recreate this anyway?
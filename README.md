# SystemC-PlayGround
This repository will hold code snippets of the lecture and exercise for the module SystemC. 
It will also hold different markdown files explaining different concepts of C++ and SystemC.

## Feedback:

- Exercise 3: kannst du den State auch mit einem "sc_signal" modellieren und dir dadurch das "current_state" und "next_state" sparen.
- Exercise 4: mit den Hierarchical PNs hab ich dem Subnet noch ein "sc_port<placeInterface> in" und ein "sc_port<placeInterface> out" gegeben und diese intern verbunden, dann ist das Verbinden auf der nächsten Hierarchie etwas einfacher. Das ist aber nicht unbedingt nötig.
- Exercise 5: brauchst du eigentlich keine Sensitivity List im Konstruktor.
- Exercise 6: solltest du eigentlic die Cycles als Delay aufaddieren anstatt einer festen Zeit. Dazu gibt es auch einen Eintrag im Forum. Die Implementierung des QK passt aber.

### English: 
- Exercise 3: Can you model the state with an "sc_signal" and thereby save the "current_state" and "next_state".
- Exercise 4: With the Hierarchical PNs, I gave the subnet an "sc_port<placeInterface> in" and an "sc_port<placeInterface> out" and connected them internally, making the connection at the next hierarchy level a bit easier. However, this is not necessarily required.
- Exercise 5: You actually don't need a Sensitivity List in the constructor.
- Exercise 6: You should actually add the cycles as a delay instead of a fixed time. There is also an entry in the forum about this. However, the implementation of the QK is correct.
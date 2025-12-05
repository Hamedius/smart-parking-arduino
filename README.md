##  Repository Contents


```
smart-parking-arduino/
│
├── README.md                      # Project documentation (this file)
│
├── src/
│   └── smart_parking.ino          # Arduino code extracted & reconstructed
│
├── docs/
│   └── Parking Management.pdf     # Original project report you provided
```

### Required Files:
| File | Description |
|------|-------------|
| `src/smart_parking.ino` | **Main Arduino code** fully implemented from your PDF |
| `docs/Parking Management.pdf` | Original full documentation |
| `README.md` | This markdown project summary |

---

##  Hardware Used

- **Arduino UNO**
- **4× IR/PIR sensors** for slot detection  
  - Connected to pins **8, 9, 10, 11**
- **DC motor** for gate  
- **L293D driver IC** to control the motor  
  - Open → Pin **6** HIGH  
  - Close → Pin **7** HIGH
- **16×2 LCD Display (LiquidCrystal)**  
  - Pins connected in Proteus to **0, 1, 2, 3, 4, 5**

---

##  System Logic

### Slot Detection
- LOW = slot *occupied*  
- HIGH = slot *free*  
- 4 sensors → real‑time 4‑slot availability  

### Gate Logic
- If **freeSlots > 0** → gate **opens automatically**  
- If **freeSlots == 0** → gate **closes**  
- Motor runs only briefly (pulse)

### LCD Display
- Line 1 → `Free: X Gate:O/C`  
- Line 2 → `S1:O/F S2:O/F S3:O/F S4:O/F`

---

##  Arduino Code

The full code is included inside:

```
src/smart_parking.ino
```

---

##  How to Run

1. Open Arduino IDE  
2. Load:  
   ```
   src/smart_parking.ino
   ```
3. Select **Arduino UNO** as board  
4. Upload the code  
5. Place objects in front of sensors to simulate cars  
6. The LCD will update and the gate will open/close automatically  

---

##  Wiring Summary

| Component | Arduino Pin |
|----------|-------------|
| Slot Sensor 1 | 8 |
| Slot Sensor 2 | 9 |
| Slot Sensor 3 | 10 |
| Slot Sensor 4 | 11 |
| Motor Driver – Open | 6 |
| Motor Driver – Close | 7 |
| LCD (rs, en, d4–d7) | 0,1,2,3,4,5 |

---

##  Author

**Hamed Nahvi**

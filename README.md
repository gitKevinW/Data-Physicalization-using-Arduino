# Foodie: A Data Physicalization Approach to Understanding Nutritional Intake

Foodie is an Arduino-based tangible interface that helps users visualize and reflect on their nutritional choices by turning abstract data into engaging physical feedback. It makes dietary information—like sodium, sugar, and fiber—easy to understand through physical food models, RFID scanning, and interactive LED feedback.

---

## Overview

**Foodie** is a data physicalization system that encourages healthy eating habits by turning nutritional values into tangible, real-time visual feedback. Users scan 3D-printed food models with embedded NFC tags using an RFID reader connected to an Arduino Uno. As food items are scanned, nutrient data (sugar, sodium, fiber) is aggregated and shown via RGB LEDs on a 5-point scale:

- **White**: Far below recommended
- **Yellow**: Slightly below
- **Green**: Ideal/Recommended
- **Blue**: Slightly above
- **Red**: At or beyond the limit

This immediate, ambient feedback gives users an intuitive understanding of how their food selections affect their daily intake, encouraging reflection and mindful decision-making.

---

## Motivation

Nutrition labels can be difficult to interpret and often fail to convey how daily meals impact cumulative nutrient intake. Digital trackers tend to overwhelm users with charts and numbers. Foodie solves this by:

- **Making nutrition tangible** via physical food models
- **Visualizing nutrient accumulation** over the course of a day
- **Encouraging playful exploration** of different food combinations
- **Supporting healthy choices** in an open-ended, CST-inspired format

Based on creativity support tools (CSTs), Foodie promotes reflection and exploration around personal dietary patterns.

---

## Design Framework

This project is grounded in **"Making Data Tangible"** by Bae et al. (2022), following their design space model of:

- **Context**: Aimed at individuals who want to explore how food choices affect health.
- **Structure**: Physical food models (3D-printed) with embedded NFC tags store nutritional values.
- **Interaction**: Scanning food models updates visual LED feedback representing aggregated sugar, sodium, and fiber values.

The system is also inspired by **Shneiderman's CST** philosophy—supporting creativity through open-ended engagement and insight.

---

## System Functionality

### Food Selection and Scanning

Users select from 3D-printed models like pizza, broccoli, ice cream, etc. Each contains an NFC tag with nutrition data sourced from:
- **Canadian Nutrient File**
- **USDA National Nutrient Database**
When scanned with the RFID reader, the Arduino reads the UID and maps it to predefined nutrient values.

# ESP32-Embedded-Web-Server
ESP32-based embedded web server hosting a live sensor dashboard with DHT22 and JSON API
# 🌐 ESP32 Embedded Web Server — Live Sensor Dashboard

**Intern ID:** URK23EC1047
**Full Name:** Beulah Jenifer P
**No. of Weeks:** 4
**Project Name:** Embedded Web Server (ESP32)
**Project Scope:** ESP32-based embedded HTTP web server hosting a live, auto-refreshing weather dashboard with real-time DHT22 sensor data, JSON REST API endpoint, and LED alert system — fully simulated on Wokwi

---

## 📌 Project Overview

This project demonstrates how an ESP32 microcontroller can host its own web server, serving a live HTML dashboard and a JSON REST API endpoint over WiFi. The ESP32 reads temperature and humidity from a DHT22 sensor every 2 seconds, updates an in-memory dashboard, and serves it to any connected client. An LED alert triggers automatically when temperature crosses a safety threshold.

---

## 🧠 Features

- ESP32 connects to WiFi and hosts an HTTP server on port 80
- Live HTML dashboard with auto-refresh every 3 seconds
- Dark-themed responsive dashboard UI
- REST API endpoint `/data` returning JSON sensor data
- Real-time DHT22 temperature and humidity readings
- LED alert system for high temperature
- Request counter tracking total dashboard hits
- Serial monitor logging of all server activity

---

## 🛠️ Tech Stack

| Component | Detail |
|---|---|
| Microcontroller | ESP32 DevKit C V4 |
| Temperature Sensor | DHT22 |
| Networking | WiFi.h + WebServer.h |
| Alert | Red LED + 1KΩ Resistor |
| Data Format | JSON (manual serialization) |
| Simulation | Wokwi |
| Language | C++ (Arduino Framework) |

---

## 🌐 Web Server Endpoints

| Endpoint | Method | Response | Description |
|---|---|---|---|
| `/` | GET | HTML | Live dashboard with temperature, humidity, status |
| `/data` | GET | JSON | Raw sensor data for API integration |

### Sample JSON Response (`/data`)

```json
{
  "device": "ESP32-WebServer",
  "intern": "Beulah Jenifer P",
  "id": "URK23EC1047",
  "temperature": 24.0,
  "humidity": 40.0,
  "status": "NORMAL",
  "requests": 12
}
```

---

## 🔌 Circuit Connections

| Component | ESP32 Pin |
|---|---|
| DHT22 VCC | 3V3 |
| DHT22 GND | GND |
| DHT22 DATA | GPIO 4 |
| LED Anode | GPIO 2 via 1KΩ |
| LED Cathode | GND |

---

## 🖥️ Dashboard Preview

The live dashboard displays:
- Current temperature in large readable format
- Current humidity percentage
- System status (Normal / Alert)
- Total server requests served
- Device IP address and auto-refresh indicator

---


## 🚨 Alert Logic

| Condition | Action |
|---|---|
| Temperature > 35.0°C | LED turns ON, status shows ALERT |
| Temperature ≤ 35.0°C | LED stays OFF, status shows NORMAL |

---


## 🎯 Key Results

| Metric | Value |
|---|---|
| Server Port | 80 (HTTP) |
| Sensor Update Rate | Every 2 seconds |
| Dashboard Auto-refresh | Every 3 seconds |
| API Endpoints | 2 (`/` and `/data`) |
| Alert Threshold | 35.0°C |
| Simulation | Wokwi — 100% online |

---

*Developed as part of CodSoft Embedded Systems Internship*

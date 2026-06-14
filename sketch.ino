/*
 * ESP32 Embedded Web Server — Live Sensor Dashboard
 * Intern: Beulah Jenifer P | URK23EC1047
 * CodSoft Embedded Systems Internship
 * Project: Embedded Web Server (ESP32)
 * Board: ESP32 | Simulation: Wokwi
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHT_PIN    4
#define DHT_TYPE   DHT22
#define LED_PIN    2
#define TEMP_ALERT 35.0

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);
DHT dht(DHT_PIN, DHT_TYPE);

float temperature = 0;
float humidity    = 0;
int   requestCount = 0;

String getHTML() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta http-equiv='refresh' content='3'>";
  html += "<title>ESP32 Weather Dashboard</title>";
  html += "<style>";
  html += "body{font-family:Arial;background:#0D1117;color:#fff;text-align:center;padding:30px;}";
  html += "h1{color:#4ECDC4;}";
  html += ".card{background:#161B22;border-radius:12px;padding:20px;margin:15px auto;max-width:300px;box-shadow:0 4px 10px rgba(0,0,0,0.5);}";
  html += ".value{font-size:48px;font-weight:bold;color:#FFD93D;}";
  html += ".label{font-size:16px;color:#8B949E;}";
  html += ".status{padding:8px;border-radius:6px;margin-top:10px;}";
  html += ".ok{background:#2ECC71;color:#000;}";
  html += ".alert{background:#FF6B6B;color:#000;}";
  html += ".footer{margin-top:30px;color:#8B949E;font-size:12px;}";
  html += "</style></head><body>";
  html += "<h1>🌐 ESP32 Live Weather Dashboard</h1>";
  
  html += "<div class='card'><div class='label'>Temperature</div>";
  html += "<div class='value'>" + String(temperature, 1) + " &deg;C</div></div>";
  
  html += "<div class='card'><div class='label'>Humidity</div>";
  html += "<div class='value'>" + String(humidity, 1) + " %</div></div>";
  
  html += "<div class='card'><div class='label'>System Status</div>";
  if (temperature > TEMP_ALERT) {
    html += "<div class='status alert'>⚠ HIGH TEMPERATURE ALERT</div>";
  } else {
    html += "<div class='status ok'>✅ NORMAL</div>";
  }
  html += "</div>";

  html += "<div class='card'><div class='label'>Server Requests</div>";
  html += "<div class='value' style='font-size:28px;'>" + String(requestCount) + "</div></div>";

  html += "<div class='footer'>EdgeSense Web Server | Beulah Jenifer P | URK23EC1047<br>";
  html += "IP: " + WiFi.localIP().toString() + " | Auto-refresh: 3s</div>";
  
  html += "</body></html>";
  return html;
}

String getJSON() {
  String json = "{";
  json += "\"device\":\"ESP32-WebServer\",";
  json += "\"intern\":\"Beulah Jenifer P\",";
  json += "\"id\":\"URK23EC1047\",";
  json += "\"temperature\":" + String(temperature, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1) + ",";
  json += "\"status\":\"" + String(temperature > TEMP_ALERT ? "ALERT" : "NORMAL") + "\",";
  json += "\"requests\":" + String(requestCount);
  json += "}";
  return json;
}

void handleRoot() {
  requestCount++;
  server.send(200, "text/html", getHTML());
  Serial.println("GET / -> Dashboard served");
}

void handleData() {
  requestCount++;
  server.send(200, "application/json", getJSON());
  Serial.println("GET /data -> JSON served");
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not Found");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();

  Serial.println("========================================");
  Serial.println("  ESP32 Embedded Web Server");
  Serial.println("  Beulah Jenifer P | CodSoft 2025");
  Serial.println("========================================");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("✅ WiFi connected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("✅ HTTP server started on port 80");
  Serial.println("📡 Open browser at: http://" + WiFi.localIP().toString());
  Serial.println();
}

void loop() {
  server.handleClient();

  static unsigned long lastRead = 0;
  if (millis() - lastRead > 2000) {
    lastRead = millis();
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (!isnan(h) && !isnan(t)) {
      humidity = h;
      temperature = t;

      digitalWrite(LED_PIN, temperature > TEMP_ALERT ? HIGH : LOW);

      Serial.print("Sensor Update -> Temp: ");
      Serial.print(temperature, 1);
      Serial.print(" C | Hum: ");
      Serial.print(humidity, 1);
      Serial.println(" %");
    }
  }
}


#include <ESP8266WiFi.h>
 
const char* ssid = "ef"; // set your wifi name here
const char* password = "12345678"; // set your wifi password here.
 
int ledPin1 = 16; // GPIO16 or for NodeMCU you can directly write D0 
int ledPin2 = 5;  // GPIO5  or for NodeMCU you can directly write D1 
int ledPin3 = 4;  // GPIO4  or for NodeMCU you can directly write D2 
int ledPin4 = 0;  // GPIO0  or for NodeMCU you can directly write D3 
WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
     
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
    value = LOW;
  }
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
    value = LOW;
  }
  if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(ledPin3, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(ledPin3, LOW);
    value = LOW;
  }
  if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(ledPin4, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(ledPin4, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn On 1 </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off 1 </button></a><br />");  
  client.println("<a href=\"/LED2=ON\"\"><button>Turn On 2 </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn Off 2 </button></a><br />");  
  client.println("<a href=\"/LED3=ON\"\"><button>Turn On 3 </button></a>");
  client.println("<a href=\"/LED3=OFF\"\"><button>Turn Off 3 </button></a><br />");  
  client.println("<a href=\"/LED4=ON\"\"><button>Turn On 4 </button></a>");
  client.println("<a href=\"/LED4=OFF\"\"><button>Turn Off 4 </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 

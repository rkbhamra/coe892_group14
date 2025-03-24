import time
import requests
import json

CLIENT_ID = "gYfTrFpxSnPsAaBugNpSbT8PLPvCQD5S"
CLIENT_SECRET = "TuyWTybxhZA2Zhj65Cw2jcuKJa7vfZh9GyJy0mNrUb4gZzW33whWNcd0RRm44GU6"
TOKEN_URL = "https://api2.arduino.cc/iot/v1/clients/token"
AUDIENCE = "https://api2.arduino.cc/iot"

def get_access_token():
    response = requests.post(TOKEN_URL, data={
        "grant_type": "client_credentials",
        "client_id": CLIENT_ID,
        "client_secret": CLIENT_SECRET,
        "audience": AUDIENCE  
    })
    if response.status_code == 200:
        data = response.json()
        return data["access_token"], data["expires_in"]
    else:
        print("Failed to get token:", response.json())
        return None, None  

access_token, expires_in = get_access_token()

expires_at = time.time() + (expires_in if expires_in else 3600)  

def ensure_valid_token():
    global access_token, expires_at
    if time.time() >= expires_at: 
        access_token, expires_in = get_access_token()
        expires_at = time.time() + (expires_in if expires_in else 3600)

def get_dashboards():
    ensure_valid_token()  
    headers = {"Authorization": f"Bearer {access_token}"}
    response = requests.get("https://api2.arduino.cc/iot/v2/dashboards", headers=headers)
    return response.json()

raw = get_dashboards()  

variables_data = []

for dashboard in raw:  
    for widget in dashboard["widgets"]:  
        widget_name = widget["options"]["name"] if "options" in widget else "Unknown"
        for variable in widget.get("variables", []): 
            variables_data.append({
                "spot": widget_name,
                "resistor": variable["name"], #leo take this out if you dont need it
                "free": variable["last_value"]
            })

print(variables_data)

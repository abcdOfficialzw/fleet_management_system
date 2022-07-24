##Import Requirements
import geocoder
import serial
import time
import datetime
import requests
import json
from flask import Flask, request
from twilio.twiml.messaging_response import MessagingResponse
#from twilio.rest import Client
app = Flask(__name__)

@app.route('/chatbot', methods = ['GET', 'POST'])
def deliveryBot():
    ##create twilio message instance
    #client = Client('AC0faf539365db81e4b6225f328f6e3c35', '488f6a50ca1c8287e8c961485b689416')
    msg = request.form.get('Body').lower()
    resp = MessagingResponse()


    ##define the 
    ip = geocoder.ip('me')

    def get_values():
        ser = serial.Serial('/dev/ttyACM0', 9800, timeout=1) #Opening port for serial connection
        time.sleep(5)
        value = ser.readline().decode().strip()
        ser.close()
        value = value.split(",")
        return value
    

    def get_time_of_day(h):
        return (
            "morning"
            if 5 <= h <= 11
            else "afternoon"
            if 12 <= h <= 17
            else "evening"
            if 18 <= h <= 22
            else "night")



    greetings = [
        'hie',
        'hi',
        'hey',
        'yoh',
        'hello',        
        'wassup',
        'how are you',
        'good morning',
        'good afternoon',
        'good evening',
        'morning',
        'afternoon',
        'evening'
    ]

    try:
        #value = get_values()
        #message = client.messages.create(
        #    body = 'Replace with disaster message',
        #    from_='whatsapp:+14155238886',
        #    to='whatsapp:+263776392244'
        #)

        if msg in get_time_of_day:
            time_of_day = get_time_of_day(datetime.datetime.now().hour)
            resp.message(
                '*Good ' + str(time_of_day) + ', I am a WhatsApp ChatBot👋🏽*\n I allow you to monitor your truck remotely'
            )
            resp.message(
                "🙂How may I be of assistance?\n"
                +"1. Check Engine Temperature.\n"
                +"2. Check Cargo Temperature.\n"
                +"3. Check Fuel Level.\n"
                +"4. Check Truck Location.\n"
            )
            return str(resp)
        elif msg == '1':
            value = get_values()
            resp.message("Your Truck's Engine Temperature is: " + value[0])
            return str(resp)
            return str(resp)
        elif msg == '2':
            value = get_values()
            resp.message("Your Truck's Cargo Temperature is: " + value[1])
            return str(resp)
        elif msg == '3':
            value = get_values()
            fuel_level = value[2]
            print(value[2])
            value = int(fuel_level)
            print(type(value))
            resp.message("Your Truck's fuel is: " + fuel_level + "/255")
            return str(resp)
        elif msg == '4':
            value = get_values()
            resp.message("Your Truck is in Harare, Zimbabwe")
            return str(resp)
        else:
            resp.message('Sorry I was unable to understand you🙁')
            return str(resp)
    except:
        resp.message('Something went wrong, May you please try that again later🙁')
        return str(resp)
if __name__ == '__main__':
    app.run(debug=True, host = '0.0.0.0', port = int(os.environ.get('PORT', 5000)))

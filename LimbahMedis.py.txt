from flask import Flask, render_template, jsonify, request
import serial
import time

app = Flask(__name__)

serial_port = serial.Serial('/dev/ttyACM0', 9600)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/ph')
def get_ph():
    if serial_port.in_waiting > 0:
        data = serial_port.readline().decode('utf-8').rstrip()
        ph_value = get_ph_value(data)
        return jsonify({'ph': ph_value})
    else:
        return jsonify({'ph': None})

def get_ph_value(data):
    start_index = data.find(':') + 1
    ph_value = data[start_index:].strip()
    return float(ph_value)

@app.route('/water_level')
def get_water_level():
    if serial_port.in_waiting > 0:
        data = serial_port.readline().decode('utf-8').rstrip()
        tandon5 = get_water_level_data(data)
        return jsonify({'tandon5': tandon5})
    else:
        return jsonify({'tandon5': None})

def get_water_level_data(data):
    start_index = data.find(':') + 1
    tandon5 = int(data[start_index:].strip())
    return tandon5

@app.route('/start')
def start_count():
    serial_port.write(b'1')
    return render_template('index.html')

@app.route('/repeat')
def repeat_count():
    serial_port.write(b'2')
    return render_template('index.html')

@app.route('/waste')
def waste_count():
    serial_port.write(b'3')
    return render_template('index.html')

@app.route('/stop')
def stop_count():
    serial_port.write(b'0')
    return render_template('index.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
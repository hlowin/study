import Jetson.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setup(37, GPIO.OUT)
GPIO.output(37, GPIO.HIGH)

GPIO.setup(35, GPIO.OUT)
GPIO.output(35, GPIO.LOW)

# GPIO.setup(13, GPIO.IN)
# GPIO.input(13)
GPIO.cleanup()

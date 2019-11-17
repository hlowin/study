import socket  
import numpy  
import cv2  

  
def getimage():
    # HOST = "192.168.100.101"
    HOST = "192.168.55.1"
    PORT = 12345  
    sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)  
    sock.connect((HOST,PORT))   
    sock.send('HELLO\n')  
    buf=''   
    recvlen=100  
    while recvlen>0:  
        receivedstr=sock.recv(1024*8)  
        recvlen=len(receivedstr)  
        buf +=receivedstr  
    sock.close()  
    narray=numpy.fromstring(buf,dtype='uint8')  
    return cv2.imdecode(narray,1)  
  
while True:  
    img = getimage()
    cv2.imshow('Capture',img)  
    if cv2.waitKey(100) & 0xFF == ord('q'):
        break
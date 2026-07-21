from ultralytics import YOLO
import cv2
import serial
import time

# LOAD MODEL
model = YOLO("runs/detect/train/weights/best.pt")

camera_index = 0
cap = cv2.VideoCapture(camera_index, cv2.CAP_DSHOW)

if not cap.isOpened():
    print("Error: Cannot open camera")
    exit()

print("Press SPACE to capture image...")
print("Press Q to quit")

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        break

    cv2.imshow("Camera Feed", frame)
    key = cv2.waitKey(1)

    if key == 32:  # SPACE
        print("Image captured!")
        break

    if key == ord("q"):
        cap.release()
        cv2.destroyAllWindows()
        exit()

cap.release()
cv2.destroyAllWindows()

results = model.predict(frame, conf=0.25, verbose=False)

if len(results[0].boxes) > 0:
    box = results[0].boxes[0]
    class_id = int(box.cls[0])
    class_name = model.names[class_id].lower().strip()

    print("Detected:", class_name)

    try:
        arduino = serial.Serial("COM6", 9600)
        time.sleep(2)

        if "nut" in class_name:
            print("Sending: 0")
            arduino.write(b'0')

        elif "bolt" in class_name:
            print("Sending: 1")
            arduino.write(b'1')

        else:
            print("Unknown object")
            arduino.close()
            exit()

        arduino.flush()
        time.sleep(1)  # ensure data is sent
        arduino.close()

    except Exception as e:
        print("Serial Error:", e)

else:
    print("No object detected")
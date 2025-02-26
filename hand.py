import cv2
import mediapipe as mp
import serial
import time

# Inisialisasi komunikasi serial ke Arduino (ubah COM sesuai dengan port Arduino)
ser = serial.Serial('COM5', 9600, timeout=1)  # Jika di Linux/Mac: '/dev/ttyUSB0'

# Inisialisasi Mediapipe untuk deteksi tangan
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7)
mp_draw = mp.solutions.drawing_utils

# Menggunakan kamera laptop
cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)  # Mirror tampilan kamera
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands.process(rgb_frame)

    # Jika ada tangan yang terdeteksi
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
            
            # Ambil koordinat jari telunjuk
            index_finger_tip = hand_landmarks.landmark[8]  # Titik ujung jari telunjuk
            if index_finger_tip.y < hand_landmarks.landmark[6].y:  # Jika telunjuk diangkat
                ser.write(b'1')  # Kirim perintah ke Arduino untuk nyalakan LED
            else:
                ser.write(b'0')  # Kirim perintah untuk matikan LED

    cv2.imshow("Hand Tracking", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
ser.close()
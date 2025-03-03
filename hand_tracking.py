import cv2
import mediapipe as mp
import serial
import time

# Inisialisasi komunikasi serial ke Arduino (ubah COM sesuai dengan yang digunakan)
ser = serial.Serial('COM7', 9600, timeout=1)

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

    finger_count = 0

    # Jika ada tangan yang terdeteksi
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

            # **Logika deteksi jari**
            finger_tips = [8, 12, 16, 20]  # ID landmark ujung jari (telunjuk, tengah, manis, kelingking)
            finger_bases = [6, 10, 14, 18] # ID landmark pangkal jari

            for tip, base in zip(finger_tips, finger_bases):
                if hand_landmarks.landmark[tip].y < hand_landmarks.landmark[base].y - 0.02:  
                    finger_count += 1

            # **Deteksi ibu jari**
            thumb_tip = hand_landmarks.landmark[4]   # Ujung ibu jari
            thumb_ip = hand_landmarks.landmark[3]    # Sendi tengah ibu jari
            thumb_base = hand_landmarks.landmark[2]  # Sendi pangkal ibu jari

            if abs(thumb_tip.x - thumb_base.x) > 0.05 and thumb_tip.y < thumb_ip.y:  
                finger_count += 1

    # Kirim data ke Arduino berdasarkan jumlah jari
    if finger_count == 1:
        ser.write(b'1')
    elif finger_count == 3:
        ser.write(b'3')
    elif finger_count == 5:
        ser.write(b'5')
    elif finger_count == 10:
        ser.write(b'0')
    
    # Tampilkan jumlah jari di layar
    cv2.putText(frame, f"Jari: {finger_count}", (50, 100), 
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("Hand Tracking", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
ser.close()

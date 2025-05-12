# Nama file input dan output
input_file = 'lamputerang.csv'
output_file = 'lamputerang.txt'  # atau output_mentah.csv kalau mau

# Baca file CSV
with open(input_file, 'r') as f:
    lines = f.readlines()

# Bersihkan spasi kosong / karakter aneh
clean_lines = [line.strip() for line in lines if line.strip()]

# Tulis ulang angka-angka ke file baru, tetap satu angka satu baris
with open(output_file, 'w') as f:
    for line in clean_lines:
        f.write(line + '\n')

print(f'File mentah berhasil dibuat: {output_file}')

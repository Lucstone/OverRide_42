hex_values = [
    "0x756e505234376848",
    "0x45414a3561733951",
    "0x377a7143574e6758",
    "0x354a35686e475873",
    "0x48336750664b394d"
]

def convert_hex_to_string(hex_values):
    result = ""
    for hex_value in hex_values:
        bytes_value = bytes.fromhex(hex_value[2:])
        little_endian_bytes = bytes_value[::-1]
        result += little_endian_bytes.decode('ascii', errors='ignore')
    return result

converted_string = convert_hex_to_string(hex_values)
print("Mot de passe :", converted_string)

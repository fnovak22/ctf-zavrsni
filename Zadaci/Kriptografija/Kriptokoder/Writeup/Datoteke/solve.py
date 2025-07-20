def shift_inv(b):
    left  = (b << 3) & 0xFF
    right = (b >> 5) & 0x07
    return left | right

def decrypt(cipher, key):
    Z = "![_°^?'I|o0]$+=-"
    zmap = {ch: i for i,ch in enumerate(Z)}
    key_bytes = key.encode("utf-8")
    key_len = len(key_bytes)
    m = bytearray()
    
    for i in range(0, len(cipher), 2):
        h = zmap[cipher[i]]
        l = zmap[cipher[i+1]]
        temp = (h << 4) | l
        k_byte = key_bytes[(i//2) % key_len]
        temp2 = temp ^ k_byte
        original = shift_inv(temp2)
        m.append(original)

    return m.decode('utf-8', errors='replace')

c = "[==]0=-+|=!^_0oI°_|$+'I$I-+$0[_oo[$__|o+$+0]?+_+!'^-+^I_|]o_o+"
key = "vaf5g-AZTFz65th/?.%"
m = decrypt(c, key)
print(m)

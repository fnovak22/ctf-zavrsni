from PIL import Image
import os

input_file_path = 'combined_output.txt'
output_file = 'output_image.png'

def get_color(value):
    if value == '0':
        return (255, 255, 255)  # Bijela
    elif value == '1':
        return (0, 0, 0)  # Crna
    elif value == '?':
        return (255, 0, 0)  # Crvena
    return (255, 255, 255)  # Default, bijela ako je nešto drugo

with open(input_file_path, 'r') as file:
    lines = file.read().strip().split('\n')

    height = len(lines)
    width = len(lines[0])

    image = Image.new('RGB', (width, height), (255, 255, 255))
    pixels = image.load()


    for y in range(height):
        for x in range(width):
            color = get_color(lines[y][x])
            pixels[x, y] = color


    output_file_path = os.path.join(os.getcwd(), output_file)
    image.save(output_file_path)
    
    print(f"Generiranje zavrseno - spremljeno kao '{output_file}'")

import os
from natsort import natsorted

def combine_files(input_dir, output_file):
    with open(output_file, 'w') as combined_file:
        txt_files = natsorted(f for f in os.listdir(input_dir) if f.endswith('.txt'))
        
        for i, filename in enumerate(txt_files):
            file_path = os.path.join(input_dir, filename)
            with open(file_path, 'r') as file:
                lines = file.readlines()
                combined_file.writelines(lines)
    
    print(f"Spajanje završeno - spremljeno kao '{output_file}'")

input_dir = 'signali'
output_file = 'combined_output.txt'
combine_files(input_dir, output_file)

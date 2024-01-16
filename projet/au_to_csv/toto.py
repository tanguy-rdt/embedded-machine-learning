import pandas as pd
import os

def combine_csv_files(base_path, output_file):
    """
    Combines all CSV files named 'descriptors.csv' located in subdirectories of the base_path into a single CSV file.
    
    Args:
    base_path (str): The base directory containing subdirectories with CSV files.
    output_file (str): The path of the output CSV file where all data will be combined.
    """
    combined_data = pd.DataFrame()

    for root, dirs, files in os.walk(base_path):
        for file in files:
            if file == 'descriptor.csv':
                full_path = os.path.join(root, file)
                print(full_path)
                csv_data = pd.read_csv(full_path)
                combined_data = pd.concat([combined_data, csv_data], ignore_index=True)

    combined_data.to_csv(output_file, index=False)

# Use the function
base_path = '../csv_files'  # Replace with your actual base path
output_file = '../csv_files/output_file.csv'  # Replace with your desired output file path
combine_csv_files(base_path, output_file)

# This will create a single CSV file combining the contents of all 'descriptors.csv' files
# found in the subdirectories of the specified base path.


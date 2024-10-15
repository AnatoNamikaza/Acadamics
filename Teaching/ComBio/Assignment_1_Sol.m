import requests
import numpy as np
import matplotlib.pyplot as plt
from Bio.PDB import PDBParser

def fetch_protein_data(accession_number):
    # Fetch the PDB file from the UniProt database
    url = f'https://files.uniprot.org/uniprot/{accession_number}.pdb'
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    else:
        print(f"Failed to retrieve data for {accession_number}. Status code: {response.status_code}")
        return None

def parse_pdb(pdb_data):
    lines = pdb_data.splitlines()
    coordinates = []

    for line in lines:
        if line.startswith("ATOM") or line.startswith("HETATM"):
            # Extract coordinates
            atom_type = line[12:16].strip()
            x = float(line[30:38])
            y = float(line[38:46])
            z = float(line[46:54])
            coordinates.append((atom_type, x, y, z))

    return coordinates

def calculate_angles(coordinates):
    phi_angles = []
    psi_angles = []

    for i in range(1, len(coordinates) - 2):
        # Calculate phi angle (N(i-1), CA(i-1), C(i))
        N_prev = coordinates[i - 1][1:4]
        CA_prev = coordinates[i][1:4]
        C_curr = coordinates[i + 1][1:4]
        phi = calculate_phi(N_prev, CA_prev, C_curr)

        # Calculate psi angle (CA(i), C(i), N(i+1))
        CA_curr = coordinates[i][1:4]
        C_curr = coordinates[i + 1][1:4]
        N_next = coordinates[i + 2][1:4]
        psi = calculate_psi(CA_curr, C_curr, N_next)

        if phi is not None and psi is not None:
            phi_angles.append(phi)
            psi_angles.append(psi)

    return phi_angles, psi_angles

def calculate_phi(N_prev, CA_prev, C_curr):
    # Add logic to calculate phi angle using vector math
    # Implement the formula for phi angle calculation here
    return phi

def calculate_psi(CA_curr, C_curr, N_next):
    # Add logic to calculate psi angle using vector math
    # Implement the formula for psi angle calculation here
    return psi

def plot_ramachandran(phi_angles, psi_angles):
    plt.figure(figsize=(8, 8))
    plt.scatter(phi_angles, psi_angles, alpha=0.5)
    plt.xlim(-180, 180)
    plt.ylim(-180, 180)
    plt.xlabel("Phi (ϕ) Angle (degrees)")
    plt.ylabel("Psi (ψ) Angle (degrees)")
    plt.title("Ramachandran Plot")
    plt.grid()
    plt.show()

# Example Usage
accession_number = "P12345"  # Replace with the actual accession number
pdb_data = fetch_protein_data(accession_number)
if pdb_data:
    coordinates = parse_pdb(pdb_data)
    phi_angles, psi_angles = calculate_angles(coordinates)
    plot_ramachandran(phi_angles, psi_angles)

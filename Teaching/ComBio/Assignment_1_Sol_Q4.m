function mz_distribution(accession_number)
    % fetching
    fasta_url = strcat('https://www.uniprot.org/uniprot/', accession_number, '.fasta');
    fasta_filename = strcat(accession_number, '.fasta');
    
    websave(fasta_filename, fasta_url);
    
    protein_sequence = extract_protein_sequence(fasta_filename);
    
    protein_mass = calculate_protein_mass(protein_sequence);
    fprintf('Protein Mass: %.2f Da\n', protein_mass);
    
    fprintf('m/z Distribution for 23 charge states:\n');
    for charge_state = 1:23
        mz_value = (protein_mass + charge_state * 1.007276) / charge_state;
        fprintf('Charge State %d: m/z = %.2f\n', charge_state, mz_value);
    end
end

function protein_sequence = extract_protein_sequence(fasta_filename)
    file_id = fopen(fasta_filename, 'r');
    data = textscan(file_id, '%s', 'Delimiter', '\n');
    fclose(file_id);
    
    protein_sequence = '';
    for i = 2:length(data{1})
        protein_sequence = strcat(protein_sequence, data{1}{i});
    end
end

function mass = calculate_protein_mass(sequence)
    % mass of each amino acid (in Daltons)
    amino_acid_masses = struct( ...
        'A', 71.0788, 'R', 156.1875, 'N', 114.1038, 'D', 115.0886, ...
        'C', 103.1388, 'E', 129.1155, 'Q', 128.1307, 'G', 57.0519, ...
        'H', 137.1411, 'I', 113.1594, 'L', 113.1594, 'K', 128.1741, ...
        'M', 131.1926, 'F', 147.1766, 'P', 97.1167, 'S', 87.0782, ...
        'T', 101.1051, 'W', 186.2132, 'Y', 163.176, 'V', 99.1326 ...
    );
    
    mass = 0;
    for i = 1:length(sequence)
        amino_acid = sequence(i);
        if isfield(amino_acid_masses, amino_acid)
            mass = mass + amino_acid_masses.(amino_acid);
        else
            warning('Unknown amino acid: %s', amino_acid);
        end
    end
end

mz_distribution('P0CG47');

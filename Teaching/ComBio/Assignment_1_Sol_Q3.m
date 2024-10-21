function ramachandran_analysis(accession_number)
    % Fetching the FASTA file from UniProt
    fasta_url = strcat('https://www.uniprot.org/uniprot/', accession_number, '.fasta');
    fasta_filename = strcat(accession_number, '.fasta');
    
    try
        websave(fasta_filename, fasta_url);
    catch
        error('Failed to fetch FASTA file. Check the accession number.');
    end
    
    % Extracting the protein sequence
    protein_sequence = extract_protein_sequence(fasta_filename);
    
    if isempty(protein_sequence)
        error('Failed to extract protein sequence.');
    end
    
    % Assuming you have a function to calculate phi and psi angles
    % [phi_angles, psi_angles] = calculate_phi_psi(protein_sequence);
    
    % Plotting Ramachandran plot (example placeholder)
    % scatter(phi_angles, psi_angles);
    % xlabel('Phi');
    % ylabel('Psi');
    % title('Ramachandran Plot');
    
    % Include further logic for angle calculation and plotting
end

function pdb_id = extract_pdb_id_from_fasta(fasta_filename)
    % Parses the FASTA file and extracts the corresponding PDB ID
    fid = fopen(fasta_filename, 'r');
    pdb_id = '';
    
    while ~feof(fid)
        line = fgetl(fid);
        if startsWith(line, '>') % Header line in FASTA format
            tokens = strsplit(line); % Split by whitespace
            for i = 1:length(tokens)
                if startsWith(tokens{i}, 'PDB:')
                    pdb_id = tokens{i}(5:end); % Extract PDB ID
                    break;
                end
            end
            if ~isempty(pdb_id)
                break; % Break if PDB ID found
            end
        end
    end
    fclose(fid);
end

function pdb_data = read_pdb(pdb_filename)
    % Reads the PDB file and extracts backbone atoms (N, CA, C)
    fid = fopen(pdb_filename, 'r');
    pdb_data = struct('N', [], 'CA', [], 'C', []); % To store coordinates
    while ~feof(fid)
        line = fgetl(fid);
        if startsWith(line, 'ATOM')
            atom_type = strtrim(line(13:16));
            x = str2double(line(31:38)); % X coordinate
            y = str2double(line(39:46)); % Y coordinate
            z = str2double(line(47:54)); % Z coordinate
            
            % Add coordinates to the respective atom type
            if strcmp(atom_type, 'N')
                pdb_data.N = [pdb_data.N; x, y, z];
            elseif strcmp(atom_type, 'CA')
                pdb_data.CA = [pdb_data.CA; x, y, z];
            elseif strcmp(atom_type, 'C')
                pdb_data.C = [pdb_data.C; x, y, z];
            end
        end
    end
    fclose(fid);
end

function [phi_angles, psi_angles] = calculate_phi_psi(pdb_data)
    % Calculates phi and psi angles for each residue
    num_residues = size(pdb_data.CA, 1);
    phi_angles = zeros(num_residues - 1, 1);
    psi_angles = zeros(num_residues - 1, 1);
    
    for i = 2:num_residues-1
        % Get coordinates of atoms for residue i
        N1 = pdb_data.N(i-1, :);   % Previous residue Nitrogen
        CA1 = pdb_data.CA(i, :);   % Current residue Alpha Carbon
        C1 = pdb_data.C(i, :);     % Current residue Carbonyl Carbon
        N2 = pdb_data.N(i, :);     % Current residue Nitrogen
        CA2 = pdb_data.CA(i+1, :); % Next residue Alpha Carbon
        
        % Calculate phi angle (N(i-1) - CA(i) - C(i) - N(i))
        phi_angles(i) = calculate_torsion_angle(N1, CA1, C1, N2);
        
        % Calculate psi angle (CA(i) - C(i) - N(i+1) - CA(i+1))
        psi_angles(i) = calculate_torsion_angle(CA1, C1, N2, CA2);
    end
end

function angle = calculate_torsion_angle(atom1, atom2, atom3, atom4)
    % Calculate torsion angle between four atoms using vector math
    b1 = atom2 - atom1;
    b2 = atom3 - atom2;
    b3 = atom4 - atom3;
    
    % Normalize the vectors
    b1 = b1 / norm(b1);
    b2 = b2 / norm(b2);
    b3 = b3 / norm(b3);
    
    % Calculate normal vectors
    n1 = cross(b1, b2);
    n2 = cross(b2, b3);
    
    % Calculate the torsion angle
    x = dot(n1, n2);
    y = dot(cross(n1, n2), b2 / norm(b2));
    angle = atan2d(y, x);
end

ramachandran_analysis('P12345');

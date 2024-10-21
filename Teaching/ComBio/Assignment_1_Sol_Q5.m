mass_ubiquitin = 8565;  % mass of ubiquitin in Daltons (8.565 kDa)
charge_states = 1:23;   % range of charge states from 1 to 23
num_isotopes = 5;       % average number of isotopic peaks

mz_values = [];  peak_count = 0;

for z = charge_states
    base_mz = mass_ubiquitin / z;

    for isotope = 0:(num_isotopes-1)
        mz = base_mz + isotope/z;
        mz_values = [mz_values; mz];
        peak_count = peak_count + 1;
    end
end

disp(['Total number of peaks: ', num2str(peak_count)]);
disp('Sample m/z values (first 10):');
disp(mz_values(1:10));
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
stem(mz_values, ones(size(mz_values)), 'filled');
xlabel('m/z (mass-to-charge ratio)');
ylabel('Relative Intensity (arbitrary units)');
title('Simulated Mass Spectrum of Ubiquitin with 23 Charge States and Isotopes');
grid on;

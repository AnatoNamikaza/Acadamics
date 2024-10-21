data = load('Ubiquitin with Random Intensity - Copy.txt');

mz_values = data(:, 1); 
intensity_values = data(:, 2); 

normalized_intensity = intensity_values / max(intensity_values);

threshold = 0.5;
significant_peaks = mz_values(normalized_intensity > threshold);
significant_intensities = normalized_intensity(normalized_intensity > threshold);

figure;
subplot(2, 1, 1);
plot(mz_values, normalized_intensity, '-b');
xlabel('m/z (Mass/Charge)');
ylabel('Normalized Intensity');
title('Original Mass Spectrum');
grid on;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2, 1, 2);
stem(significant_peaks, significant_intensities, '-r', 'LineWidth', 1.5);
xlabel('m/z (Mass/Charge)');
ylabel('Significant Peaks (Intensity > 50%)');
title('Tuned Mass Spectrum with Significant Peaks');
grid on;


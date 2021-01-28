% GRAFICI: Plot del grafico

close all;
clear all;
clc;

fprintf('Esercizio 2 Algoritmi e Strutture Dati:\tInizio\n');
% Leggo da file le 3 colonne NUM_OP | HT | RBT
TAB = readtable('results.txt'); 
% disp(TAB); % Controllo vada tutto bene

% Salvataggio informazioni: Attenzione, sto lavorando con i Cell Array
NUM_OP = TAB{:,1}; % Mi salvo il numero di operazioni: (asse x)
HT = TAB{:,2}; % Mi salvo i tempi per le HT
RBT = TAB{:,3}; % Mi salvo i tempi per gli rbt

% Faccio il plot
p = plot(NUM_OP, HT, NUM_OP, RBT);
grid on;
title('Esercizio 2 Algoritmi e Strutture Dati');
xlabel('Num. di operazioni');
ylabel('Tempo medio');
legend('Hash Table', 'Red Black Tree');
% Gestisco lo stile delle curve
% p(1) = prima curva
% p(2) = seconda curva
p(1).LineWidth = 2;
p(2).LineWidth = 2;
% plot(NUM_OP, HT,  NUM_OP, RBT);
fprintf('Esercizio 2 Algoritmi e Strutture Dati:\tFine\n');



% Ricorda (ho rimosso il source control in: ENVIRONMENTS - preferences -
% MATLAB - general - Source Control.
% Se voglio aggiornare con Git devo riabilitarlo
# Definisco un array di qualche elemento
A = [3, 7, 10, 12, 14, 15, 16, 17, 19, 20]
print(A)  # Stampo l'array
for i in range(len(A)):
    if(A[i] < A[i+1]):  # voglio che sia vera questa proprietà
        continue
    else:
        print("Proprietà non rispettata per: ", A[i])
        exit(1)

def consumo(km, litros):
    return km / litros

km = float(input('Quantos quilômetros foram rodados? '))
litros = float(input('Quantos litros foram gastos? '))

print(f'Consumo (km/l): {consumo(km, litros):.2f}')

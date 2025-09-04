from cs50 import get_float

while True:
    change = get_float("Change: ")
    if change >= 0:
        break

money = 0
coins = [.25, .1, .05, .01]

for i in range(len(coins)):
    remainder = round(change % coins[i], 2)
    money = money + ((change - remainder) / coins[i])
    if remainder == 0:
        break
    else:
        change = remainder

print(f"{int(round(money , 0))}")

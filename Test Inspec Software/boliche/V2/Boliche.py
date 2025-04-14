def computa_placar(s):
    
    total, i, roll = 0, 0, 0
    len_s = len(s)
    frame = 1
    
    while i < len_s and frame <= 10:
        c = s[i]
        
        if c == 'X':
            total += 10
            
            # Bônus do strike - próximos 2 lançamentos
            if i+1 < len_s:

                next1 = s[i+1]
                if next1 == 'X':
                    total += 10
                elif next1.isdigit():
                    total += int(next1)
                
                if i+2 < len_s:

                    next2 = s[i+2]

                    if next2 == 'X':
                        total += 10
                    elif next2 == '/':
                        prev = int(s[i+1]) if s[i+1].isdigit() else 0
                        total += (10 - prev)
                    elif next2.isdigit():
                        total += int(next2)

            frame += 1
            roll = 0
            i += 1

        elif c == '/':

            prev = int(s[i-1]) if s[i-1].isdigit() else 0
            total += (10 - prev)
            
            # Bônus do spare - próximo lançamento
            if i+1 < len_s:

                next_c = s[i+1]
                if next_c == 'X':
                    total += 10
                elif next_c.isdigit():
                    total += int(next_c)

            frame += 1
            roll = 0
            i += 1

        elif c.isdigit():

            total += int(c)
            roll += 1

            if roll == 2:
                frame += 1
                roll = 0
            i += 1

        elif c == '-':

            roll += 1

            if roll == 2:
                frame += 1
                roll = 0
            i += 1
            
        else:
            i += 1
    
    return total
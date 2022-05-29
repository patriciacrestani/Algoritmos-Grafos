    
import sys
MAX = sys.maxsize

controle = True
while(controle):
    n, m, c, k = input().split()
    n = int(n) # o numero de cidades do pais
    m = int(m) # o numero de estradas
    c = int(c) # o numero de cidades na rota de servico
    k = int(k) # a cidade em que o veículo foi consertado

    if(n == 0 and m == 0 and c == 0 and k == 0):
        controle = False
        continue

    if(4 > n or n > 250):
        controle = False
        continue

    if(3 > m or m > (n*(n-1)/2)):
        controle = False
        continue

    if(2 > c or c > (n-1)):
        controle = False
        continue

    if(c > k or k > (n-1)):
        controle = False
        continue

    g = [[0 for x in range(n)] for y in range(n)] 
    adj = [0 for l in range(n)] 
    q = [0 for k in range(n)] 
    for i in range (n):
        adj[i] = MAX
        for j in range(n):
            g[i][j] = MAX
    
    for i in range(m):
        u, v, p = input().split()  # ler aresta de u para v com custo p
        u = int(u) # cidade origem
        v = int(v) # cidade destino
        p = int(p) # pedagio da estrada

        if(0 > u):
            controle = False
            continue

        if(v > (n-1)):
            controle = False
            continue

        if(u == v):
            controle = False
            continue

        if(0 > p or p > 250):
            controle = False
            continue


        if (u >= c and v >= c):
            g[u][v] = p 
            g[v][u] = p

        if (u >= c and v < c):
            g[u][v] = p

        if (u < c and v >= c):
            g[v][u] = p

        if (u < c and v < c and abs(u - v) == 1):
            g[u][v] = p
            g[v][u] = p
        
    adj[k] = 0
    q.append(k)
    while (len(q) != 0):
        i = q[0]
        q.pop(0)
        for j in range(n):
            if (g[i][j] != MAX and adj[j] > (adj[i] + g[i][j])):
                adj[j] = adj[i] + g[i][j]
                q.append(j)
    print(adj[c-1])

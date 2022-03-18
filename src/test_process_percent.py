import os


if __name__ == '__main__':
    
    a = "1 (systemd) S 0 1 1 0 -1 4210944 23374 530366 51 199 256 171 2479 592 20 0 1 0 393 179470336 3268 18446744073709551615 1 1 0 0 0 0 671173123 4096 1260 0 0 0 17 4 0 0 16 0 0 0 0 0 0 0 0 0 0"
    lst = a.split()
    print(lst[13:22])
    hertz=os.sysconf("SC_CLK_TCK")
    print(hertz)
    while(1==1):
        for x in range(0,1000):
            print(x)



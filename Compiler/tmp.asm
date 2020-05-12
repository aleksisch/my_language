00000000  7F45              jg 0x47
00000002  4C                rex.wr
00000003  460201            add r8b,[rcx]
00000006  0100              add [rax],eax
00000008  0000              add [rax],al
0000000A  0000              add [rax],al
0000000C  0000              add [rax],al
0000000E  0000              add [rax],al
00000010  0200              add al,[rax]
00000012  3E0001            add [ds:rcx],al
00000015  0000              add [rax],al
00000017  007802            add [rax+0x2],bh
0000001A  400000            add [rax],al
0000001D  0000              add [rax],al
0000001F  004000            add [rax+0x0],al
00000022  0000              add [rax],al
00000024  0000              add [rax],al
00000026  0000              add [rax],al
00000028  0000              add [rax],al
0000002A  0000              add [rax],al
0000002C  0000              add [rax],al
0000002E  0000              add [rax],al
00000030  0000              add [rax],al
00000032  0000              add [rax],al
00000034  3800              cmp [rax],al
00000036  3800              cmp [rax],al
00000038  0100              add [rax],eax
0000003A  400000            add [rax],al
0000003D  0000              add [rax],al
0000003F  0001              add [rcx],al
00000041  0000              add [rax],al
00000043  0007              add [rdi],al
00000045  0000              add [rax],al
00000047  0000              add [rax],al
00000049  0000              add [rax],al
0000004B  0000              add [rax],al
0000004D  0000              add [rax],al
0000004F  0000              add [rax],al
00000051  004000            add [rax+0x0],al
00000054  0000              add [rax],al
00000056  0000              add [rax],al
00000058  0000              add [rax],al
0000005A  400000            add [rax],al
0000005D  0000              add [rax],al
0000005F  003E              add [rsi],bh
00000061  0000              add [rax],al
00000063  0000              add [rax],al
00000065  0000              add [rax],al
00000067  003E              add [rsi],bh
00000069  0000              add [rax],al
0000006B  0000              add [rax],al
0000006D  0000              add [rax],al
0000006F  0001              add [rcx],al
00000071  0000              add [rax],al
00000073  0000              add [rax],al
00000075  0000              add [rax],al
00000077  007F45            add [rdi+0x45],bh
0000007A  4C                rex.wr
0000007B  460201            add r8b,[rcx]
0000007E  0100              add [rax],eax
00000080  0000              add [rax],al
00000082  0000              add [rax],al
00000084  0000              add [rax],al
00000086  0000              add [rax],al
00000088  0200              add al,[rax]
0000008A  3E0001            add [ds:rcx],al
0000008D  0000              add [rax],al
0000008F  008000400000      add [rax+0x4000],al
00000095  0000              add [rax],al
00000097  004000            add [rax+0x0],al
0000009A  0000              add [rax],al
0000009C  0000              add [rax],al
0000009E  0000              add [rax],al
000000A0  400100            add [rax],eax
000000A3  0000              add [rax],al
000000A5  0000              add [rax],al
000000A7  0000              add [rax],al
000000A9  0000              add [rax],al
000000AB  004000            add [rax+0x0],al
000000AE  3800              cmp [rax],al
000000B0  0100              add [rax],eax
000000B2  400003            add [rbx],al
000000B5  0002              add [rdx],al
000000B7  0001              add [rcx],al
000000B9  0000              add [rax],al
000000BB  000500000000      add [rel 0xc1],al
000000C1  0000              add [rax],al
000000C3  0000              add [rax],al
000000C5  0000              add [rax],al
000000C7  0000              add [rax],al
000000C9  004000            add [rax+0x0],al
000000CC  0000              add [rax],al
000000CE  0000              add [rax],al
000000D0  0000              add [rax],al
000000D2  400000            add [rax],al
000000D5  0000              add [rax],al
000000D7  002E              add [rsi],ch
000000D9  0100              add [rax],eax
000000DB  0000              add [rax],al
000000DD  0000              add [rax],al
000000DF  002E              add [rsi],ch
000000E1  0100              add [rax],eax
000000E3  0000              add [rax],al
000000E5  0000              add [rax],al
000000E7  0000              add [rax],al
000000E9  0020              add [rax],ah
000000EB  0000              add [rax],al
000000ED  0000              add [rax],al
000000EF  0000              add [rax],al
000000F1  0000              add [rax],al
000000F3  0000              add [rax],al
000000F5  0000              add [rax],al
000000F7  00EB              add bl,ch
000000F9  03EB              add ebp,ebx
000000FB  7130              jno 0x12d
000000FD  41B90A000000      mov r9d,0xa
00000103  4883F800          cmp rax,byte +0x0
00000107  741A              jz 0x123
00000109  B900000000        mov ecx,0x0
0000010E  4883F800          cmp rax,byte +0x0
00000112  741B              jz 0x12f
00000114  4831D2            xor rdx,rdx
00000117  49F7F1            div r9
0000011A  80C230            add dl,0x30
0000011D  52                push rdx
0000011E  48FFC1            inc rcx
00000121  EBEB              jmp short 0x10e
00000123  BF30000000        mov edi,0x30
00000128  E81B000000        call 0x148
0000012D  EB11              jmp short 0x140
0000012F  4883F900          cmp rcx,byte +0x0
00000133  740B              jz 0x140
00000135  5A                pop rdx
00000136  E80D000000        call 0x148
0000013B  48FFC9            dec rcx
0000013E  EBEF              jmp short 0x12f
00000140  B20A              mov dl,0xa
00000142  E801000000        call 0x148
00000147  C3                ret
00000148  88142584004000    mov [0x400084],dl
0000014F  48BE840040000000  mov rsi,0x400084
         -0000
00000159  B801000000        mov eax,0x1
0000015E  BF00000000        mov edi,0x0
00000163  BA01000000        mov edx,0x1
00000168  51                push rcx
00000169  0F05              syscall
0000016B  59                pop rcx
0000016C  C3                ret
0000016D  4D31C0            xor r8,r8
00000170  B803000000        mov eax,0x3
00000175  BB02000000        mov ebx,0x2
0000017A  B984004000        mov ecx,0x400084
0000017F  BA01000000        mov edx,0x1
00000184  CD80              int 0x80
00000186  803C25840040000A  cmp byte [0x400084],0xa
0000018E  7415              jz 0x1a5
00000190  4D6BC00A          imul r8,r8,byte +0xa
00000194  4831C0            xor rax,rax
00000197  8A042584004000    mov al,[0x400084]
0000019E  2C30              sub al,0x30
000001A0  4901C0            add r8,rax
000001A3  EBCB              jmp short 0x170
000001A5  C3                ret
000001A6  002E              add [rsi],ch
000001A8  7368              jnc 0x212
000001AA  7374              jnc 0x220
000001AC  7274              jc 0x222
000001AE  61                db 0x61
000001AF  62                db 0x62
000001B0  002E              add [rsi],ch
000001B2  7465              jz 0x219
000001B4  7874              js 0x22a
000001B6  0000              add [rax],al
000001B8  0000              add [rax],al
000001BA  0000              add [rax],al
000001BC  0000              add [rax],al
000001BE  0000              add [rax],al
000001C0  0000              add [rax],al
000001C2  0000              add [rax],al
000001C4  0000              add [rax],al
000001C6  0000              add [rax],al
000001C8  0000              add [rax],al
000001CA  0000              add [rax],al
000001CC  0000              add [rax],al
000001CE  0000              add [rax],al
000001D0  0000              add [rax],al
000001D2  0000              add [rax],al
000001D4  0000              add [rax],al
000001D6  0000              add [rax],al
000001D8  0000              add [rax],al
000001DA  0000              add [rax],al
000001DC  0000              add [rax],al
000001DE  0000              add [rax],al
000001E0  0000              add [rax],al
000001E2  0000              add [rax],al
000001E4  0000              add [rax],al
000001E6  0000              add [rax],al
000001E8  0000              add [rax],al
000001EA  0000              add [rax],al
000001EC  0000              add [rax],al
000001EE  0000              add [rax],al
000001F0  0000              add [rax],al
000001F2  0000              add [rax],al
000001F4  0000              add [rax],al
000001F6  0000              add [rax],al
000001F8  0B00              or eax,[rax]
000001FA  0000              add [rax],al
000001FC  0100              add [rax],eax
000001FE  0000              add [rax],al
00000200  06                db 0x06
00000201  0000              add [rax],al
00000203  0000              add [rax],al
00000205  0000              add [rax],al
00000207  008000400000      add [rax+0x4000],al
0000020D  0000              add [rax],al
0000020F  008000000000      add [rax+0x0],al
00000215  0000              add [rax],al
00000217  00AE00000000      add [rsi+0x0],ch
0000021D  0000              add [rax],al
0000021F  0000              add [rax],al
00000221  0000              add [rax],al
00000223  0000              add [rax],al
00000225  0000              add [rax],al
00000227  0010              add [rax],dl
00000229  0000              add [rax],al
0000022B  0000              add [rax],al
0000022D  0000              add [rax],al
0000022F  0000              add [rax],al
00000231  0000              add [rax],al
00000233  0000              add [rax],al
00000235  0000              add [rax],al
00000237  0001              add [rcx],al
00000239  0000              add [rax],al
0000023B  0003              add [rbx],al
0000023D  0000              add [rax],al
0000023F  0000              add [rax],al
00000241  0000              add [rax],al
00000243  0000              add [rax],al
00000245  0000              add [rax],al
00000247  0000              add [rax],al
00000249  0000              add [rax],al
0000024B  0000              add [rax],al
0000024D  0000              add [rax],al
0000024F  002E              add [rsi],ch
00000251  0100              add [rax],eax
00000253  0000              add [rax],al
00000255  0000              add [rax],al
00000257  0011              add [rcx],dl
00000259  0000              add [rax],al
0000025B  0000              add [rax],al
0000025D  0000              add [rax],al
0000025F  0000              add [rax],al
00000261  0000              add [rax],al
00000263  0000              add [rax],al
00000265  0000              add [rax],al
00000267  0001              add [rcx],al
00000269  0000              add [rax],al
0000026B  0000              add [rax],al
0000026D  0000              add [rax],al
0000026F  0000              add [rax],al
00000271  0000              add [rax],al
00000273  0000              add [rax],al
00000275  0000              add [rax],al
00000277  004889            add [rax-0x77],cl
0000027A  E548              in eax,0x48
0000027C  81ECF0000000      sub esp,0xf0
00000282  E983000000        jmp 0x30a
00000287  49BF010000000000  mov r15,0x1
         -0000
00000291  4157              push r15
00000293  8F45F0            pop qword [rbp-0x10]
00000296  49BF010000000000  mov r15,0x1
         -0000
000002A0  4157              push r15
000002A2  8F45E8            pop qword [rbp-0x18]
000002A5  FF75F8            push qword [rbp-0x8]
000002A8  49BF020000000000  mov r15,0x2
         -0000
000002B2  4157              push r15
000002B4  5B                pop rbx
000002B5  58                pop rax
000002B6  4839D8            cmp rax,rbx
000002B9  0F8E38000000      jng near 0x2f7
000002BF  FF75F8            push qword [rbp-0x8]
000002C2  49BF010000000000  mov r15,0x1
         -0000
000002CC  4157              push r15
000002CE  58                pop rax
000002CF  5B                pop rbx
000002D0  4829D8            sub rax,rbx
000002D3  50                push rax
000002D4  8F45F8            pop qword [rbp-0x8]
000002D7  FF75E8            push qword [rbp-0x18]
000002DA  8F45E0            pop qword [rbp-0x20]
000002DD  FF75E8            push qword [rbp-0x18]
000002E0  FF75F0            push qword [rbp-0x10]
000002E3  58                pop rax
000002E4  5B                pop rbx
000002E5  4801D8            add rax,rbx
000002E8  50                push rax
000002E9  8F45E8            pop qword [rbp-0x18]
000002EC  FF75E0            push qword [rbp-0x20]
000002EF  8F45F0            pop qword [rbp-0x10]
000002F2  E9AEFFFFFF        jmp 0x2a5
000002F7  FF75E8            push qword [rbp-0x18]
000002FA  58                pop rax
000002FB  C3                ret
000002FC  49BF0A1A00000000  mov r15,0x1a0a
         -0000
00000306  4157              push r15
00000308  58                pop rax
00000309  C3                ret
0000030A  E9EE010000        jmp 0x4fd
0000030F  FF75D0            push qword [rbp-0x30]
00000312  49BF020000000000  mov r15,0x2
         -0000
0000031C  4157              push r15
0000031E  5B                pop rbx
0000031F  58                pop rax
00000320  4839D8            cmp rax,rbx
00000323  0F870E000000      ja near 0x337
00000329  49BF010000000000  mov r15,0x1
         -0000
00000333  4157              push r15
00000335  58                pop rax
00000336  C3                ret
00000337  FF75D0            push qword [rbp-0x30]
0000033A  49BF010000000000  mov r15,0x1
         -0000
00000344  4157              push r15
00000346  58                pop rax
00000347  5B                pop rbx
00000348  4829D8            sub rax,rbx
0000034B  50                push rax
0000034C  8F4518            pop qword [rbp+0x18]
0000034F  FF7520            push qword [rbp+0x20]
00000352  FF7528            push qword [rbp+0x28]
00000355  FF7530            push qword [rbp+0x30]
00000358  FF7538            push qword [rbp+0x38]
0000035B  FF7540            push qword [rbp+0x40]
0000035E  FF7548            push qword [rbp+0x48]
00000361  FF7550            push qword [rbp+0x50]
00000364  FF7558            push qword [rbp+0x58]
00000367  FF7560            push qword [rbp+0x60]
0000036A  FF7568            push qword [rbp+0x68]
0000036D  FF7570            push qword [rbp+0x70]
00000370  FF7578            push qword [rbp+0x78]
00000373  FF7580            push qword [rbp-0x80]
00000376  FF7588            push qword [rbp-0x78]
00000379  FF7590            push qword [rbp-0x70]
0000037C  FF7598            push qword [rbp-0x68]
0000037F  FF75A0            push qword [rbp-0x60]
00000382  FF75A8            push qword [rbp-0x58]
00000385  FF75B0            push qword [rbp-0x50]
00000388  FF75B8            push qword [rbp-0x48]
0000038B  FF75C0            push qword [rbp-0x40]
0000038E  FF75C8            push qword [rbp-0x38]
00000391  FF75D0            push qword [rbp-0x30]
00000394  FF75D8            push qword [rbp-0x28]
00000397  FF75E0            push qword [rbp-0x20]
0000039A  FF75E8            push qword [rbp-0x18]
0000039D  FF75F0            push qword [rbp-0x10]
000003A0  FF75F8            push qword [rbp-0x8]
000003A3  FF7500            push qword [rbp+0x0]
000003A6  FF7518            push qword [rbp+0x18]
000003A9  8F45D0            pop qword [rbp-0x30]
000003AC  E85EFFFFFF        call 0x30f
000003B1  50                push rax
000003B2  8F4518            pop qword [rbp+0x18]
000003B5  8F4500            pop qword [rbp+0x0]
000003B8  8F45F8            pop qword [rbp-0x8]
000003BB  8F45F0            pop qword [rbp-0x10]
000003BE  8F45E8            pop qword [rbp-0x18]
000003C1  8F45E0            pop qword [rbp-0x20]
000003C4  8F45D8            pop qword [rbp-0x28]
000003C7  8F45D0            pop qword [rbp-0x30]
000003CA  8F45C8            pop qword [rbp-0x38]
000003CD  8F45C0            pop qword [rbp-0x40]
000003D0  8F45B8            pop qword [rbp-0x48]
000003D3  8F45B0            pop qword [rbp-0x50]
000003D6  8F45A8            pop qword [rbp-0x58]
000003D9  8F45A0            pop qword [rbp-0x60]
000003DC  8F4598            pop qword [rbp-0x68]
000003DF  8F4590            pop qword [rbp-0x70]
000003E2  8F4588            pop qword [rbp-0x78]
000003E5  8F4580            pop qword [rbp-0x80]
000003E8  8F4578            pop qword [rbp+0x78]
000003EB  8F4570            pop qword [rbp+0x70]
000003EE  8F4568            pop qword [rbp+0x68]
000003F1  8F4560            pop qword [rbp+0x60]
000003F4  8F4558            pop qword [rbp+0x58]
000003F7  8F4550            pop qword [rbp+0x50]
000003FA  8F4548            pop qword [rbp+0x48]
000003FD  8F4540            pop qword [rbp+0x40]
00000400  8F4538            pop qword [rbp+0x38]
00000403  8F4530            pop qword [rbp+0x30]
00000406  8F4528            pop qword [rbp+0x28]
00000409  8F4520            pop qword [rbp+0x20]
0000040C  FF7518            push qword [rbp+0x18]
0000040F  FF75D0            push qword [rbp-0x30]
00000412  49BF020000000000  mov r15,0x2
         -0000
0000041C  4157              push r15
0000041E  58                pop rax
0000041F  5B                pop rbx
00000420  4829D8            sub rax,rbx
00000423  50                push rax
00000424  8F4518            pop qword [rbp+0x18]
00000427  FF7520            push qword [rbp+0x20]
0000042A  FF7528            push qword [rbp+0x28]
0000042D  FF7530            push qword [rbp+0x30]
00000430  FF7538            push qword [rbp+0x38]
00000433  FF7540            push qword [rbp+0x40]
00000436  FF7548            push qword [rbp+0x48]
00000439  FF7550            push qword [rbp+0x50]
0000043C  FF7558            push qword [rbp+0x58]
0000043F  FF7560            push qword [rbp+0x60]
00000442  FF7568            push qword [rbp+0x68]
00000445  FF7570            push qword [rbp+0x70]
00000448  FF7578            push qword [rbp+0x78]
0000044B  FF7580            push qword [rbp-0x80]
0000044E  FF7588            push qword [rbp-0x78]
00000451  FF7590            push qword [rbp-0x70]
00000454  FF7598            push qword [rbp-0x68]
00000457  FF75A0            push qword [rbp-0x60]
0000045A  FF75A8            push qword [rbp-0x58]
0000045D  FF75B0            push qword [rbp-0x50]
00000460  FF75B8            push qword [rbp-0x48]
00000463  FF75C0            push qword [rbp-0x40]
00000466  FF75C8            push qword [rbp-0x38]
00000469  FF75D0            push qword [rbp-0x30]
0000046C  FF75D8            push qword [rbp-0x28]
0000046F  FF75E0            push qword [rbp-0x20]
00000472  FF75E8            push qword [rbp-0x18]
00000475  FF75F0            push qword [rbp-0x10]
00000478  FF75F8            push qword [rbp-0x8]
0000047B  FF7500            push qword [rbp+0x0]
0000047E  FF7518            push qword [rbp+0x18]
00000481  8F45D0            pop qword [rbp-0x30]
00000484  E886FEFFFF        call 0x30f
00000489  50                push rax
0000048A  8F4518            pop qword [rbp+0x18]
0000048D  8F4500            pop qword [rbp+0x0]
00000490  8F45F8            pop qword [rbp-0x8]
00000493  8F45F0            pop qword [rbp-0x10]
00000496  8F45E8            pop qword [rbp-0x18]
00000499  8F45E0            pop qword [rbp-0x20]
0000049C  8F45D8            pop qword [rbp-0x28]
0000049F  8F45D0            pop qword [rbp-0x30]
000004A2  8F45C8            pop qword [rbp-0x38]
000004A5  8F45C0            pop qword [rbp-0x40]
000004A8  8F45B8            pop qword [rbp-0x48]
000004AB  8F45B0            pop qword [rbp-0x50]
000004AE  8F45A8            pop qword [rbp-0x58]
000004B1  8F45A0            pop qword [rbp-0x60]
000004B4  8F4598            pop qword [rbp-0x68]
000004B7  8F4590            pop qword [rbp-0x70]
000004BA  8F4588            pop qword [rbp-0x78]
000004BD  8F4580            pop qword [rbp-0x80]
000004C0  8F4578            pop qword [rbp+0x78]
000004C3  8F4570            pop qword [rbp+0x70]
000004C6  8F4568            pop qword [rbp+0x68]
000004C9  8F4560            pop qword [rbp+0x60]
000004CC  8F4558            pop qword [rbp+0x58]
000004CF  8F4550            pop qword [rbp+0x50]
000004D2  8F4548            pop qword [rbp+0x48]
000004D5  8F4540            pop qword [rbp+0x40]
000004D8  8F4538            pop qword [rbp+0x38]
000004DB  8F4530            pop qword [rbp+0x30]
000004DE  8F4528            pop qword [rbp+0x28]
000004E1  8F4520            pop qword [rbp+0x20]
000004E4  FF7518            push qword [rbp+0x18]
000004E7  58                pop rax
000004E8  5B                pop rbx
000004E9  4801D8            add rax,rbx
000004EC  50                push rax
000004ED  58                pop rax
000004EE  C3                ret
000004EF  49BF0A1A00000000  mov r15,0x1a0a
         -0000
000004F9  4157              push r15
000004FB  58                pop rax
000004FC  C3                ret
000004FD  E8F8FBFFFF        call 0xfa
00000502  4150              push r8
00000504  8F45F8            pop qword [rbp-0x8]
00000507  49BF010000000000  mov r15,0x1
         -0000
00000511  4157              push r15
00000513  8F45C8            pop qword [rbp-0x38]
00000516  FF75C8            push qword [rbp-0x38]
00000519  FF75F8            push qword [rbp-0x8]
0000051C  5B                pop rbx
0000051D  58                pop rax
0000051E  4839D8            cmp rax,rbx
00000521  0F83E9000000      jnc near 0x610
00000527  FF75C8            push qword [rbp-0x38]
0000052A  8F4518            pop qword [rbp+0x18]
0000052D  FF7520            push qword [rbp+0x20]
00000530  FF7528            push qword [rbp+0x28]
00000533  FF7530            push qword [rbp+0x30]
00000536  FF7538            push qword [rbp+0x38]
00000539  FF7540            push qword [rbp+0x40]
0000053C  FF7548            push qword [rbp+0x48]
0000053F  FF7550            push qword [rbp+0x50]
00000542  FF7558            push qword [rbp+0x58]
00000545  FF7560            push qword [rbp+0x60]
00000548  FF7568            push qword [rbp+0x68]
0000054B  FF7570            push qword [rbp+0x70]
0000054E  FF7578            push qword [rbp+0x78]
00000551  FF7580            push qword [rbp-0x80]
00000554  FF7588            push qword [rbp-0x78]
00000557  FF7590            push qword [rbp-0x70]
0000055A  FF7598            push qword [rbp-0x68]
0000055D  FF75A0            push qword [rbp-0x60]
00000560  FF75A8            push qword [rbp-0x58]
00000563  FF75B0            push qword [rbp-0x50]
00000566  FF75B8            push qword [rbp-0x48]
00000569  FF75C0            push qword [rbp-0x40]
0000056C  FF75C8            push qword [rbp-0x38]
0000056F  FF75D0            push qword [rbp-0x30]
00000572  FF75D8            push qword [rbp-0x28]
00000575  FF75E0            push qword [rbp-0x20]
00000578  FF75E8            push qword [rbp-0x18]
0000057B  FF75F0            push qword [rbp-0x10]
0000057E  FF75F8            push qword [rbp-0x8]
00000581  FF7500            push qword [rbp+0x0]
00000584  FF7518            push qword [rbp+0x18]
00000587  8F45F8            pop qword [rbp-0x8]
0000058A  E8F8FCFFFF        call 0x287
0000058F  50                push rax
00000590  8F4518            pop qword [rbp+0x18]
00000593  8F4500            pop qword [rbp+0x0]
00000596  8F45F8            pop qword [rbp-0x8]
00000599  8F45F0            pop qword [rbp-0x10]
0000059C  8F45E8            pop qword [rbp-0x18]
0000059F  8F45E0            pop qword [rbp-0x20]
000005A2  8F45D8            pop qword [rbp-0x28]
000005A5  8F45D0            pop qword [rbp-0x30]
000005A8  8F45C8            pop qword [rbp-0x38]
000005AB  8F45C0            pop qword [rbp-0x40]
000005AE  8F45B8            pop qword [rbp-0x48]
000005B1  8F45B0            pop qword [rbp-0x50]
000005B4  8F45A8            pop qword [rbp-0x58]
000005B7  8F45A0            pop qword [rbp-0x60]
000005BA  8F4598            pop qword [rbp-0x68]
000005BD  8F4590            pop qword [rbp-0x70]
000005C0  8F4588            pop qword [rbp-0x78]
000005C3  8F4580            pop qword [rbp-0x80]
000005C6  8F4578            pop qword [rbp+0x78]
000005C9  8F4570            pop qword [rbp+0x70]
000005CC  8F4568            pop qword [rbp+0x68]
000005CF  8F4560            pop qword [rbp+0x60]
000005D2  8F4558            pop qword [rbp+0x58]
000005D5  8F4550            pop qword [rbp+0x50]
000005D8  8F4548            pop qword [rbp+0x48]
000005DB  8F4540            pop qword [rbp+0x40]
000005DE  8F4538            pop qword [rbp+0x38]
000005E1  8F4530            pop qword [rbp+0x30]
000005E4  8F4528            pop qword [rbp+0x28]
000005E7  8F4520            pop qword [rbp+0x20]
000005EA  FF7518            push qword [rbp+0x18]
000005ED  58                pop rax
000005EE  E805FBFFFF        call 0xf8
000005F3  FF75C8            push qword [rbp-0x38]
000005F6  49BF010000000000  mov r15,0x1
         -0000
00000600  4157              push r15
00000602  58                pop rax
00000603  5B                pop rbx
00000604  4801D8            add rax,rbx
00000607  50                push rax
00000608  8F45C8            pop qword [rbp-0x38]
0000060B  E906FFFFFF        jmp 0x516
00000610  49BF000000000000  mov r15,0x0
         -0000
0000061A  4157              push r15
0000061C  8F45C0            pop qword [rbp-0x40]
0000061F  49BF000000000000  mov r15,0x0
         -0000
00000629  4157              push r15
0000062B  8F45B8            pop qword [rbp-0x48]
0000062E  49BF000000000000  mov r15,0x0
         -0000
00000638  4157              push r15
0000063A  8F45B0            pop qword [rbp-0x50]
0000063D  E8B8FAFFFF        call 0xfa
00000642  4150              push r8
00000644  8F45C0            pop qword [rbp-0x40]
00000647  E8AEFAFFFF        call 0xfa
0000064C  4150              push r8
0000064E  8F45B8            pop qword [rbp-0x48]
00000651  E8A4FAFFFF        call 0xfa
00000656  4150              push r8
00000658  8F45B0            pop qword [rbp-0x50]
0000065B  FF75B8            push qword [rbp-0x48]
0000065E  FF75B8            push qword [rbp-0x48]
00000661  58                pop rax
00000662  5B                pop rbx
00000663  480FAFC3          imul rax,rbx
00000667  50                push rax
00000668  49BF040000000000  mov r15,0x4
         -0000
00000672  4157              push r15
00000674  FF75C0            push qword [rbp-0x40]
00000677  FF75B0            push qword [rbp-0x50]
0000067A  58                pop rax
0000067B  5B                pop rbx
0000067C  480FAFC3          imul rax,rbx
00000680  50                push rax
00000681  58                pop rax
00000682  5B                pop rbx
00000683  480FAFC3          imul rax,rbx
00000687  50                push rax
00000688  58                pop rax
00000689  5B                pop rbx
0000068A  4829D8            sub rax,rbx
0000068D  50                push rax
0000068E  8F45A8            pop qword [rbp-0x58]
00000691  49BFFFFFFFFFFFFF  mov r15,0xffffffffffffffff
         -FFFF
0000069B  4157              push r15
0000069D  FF75B8            push qword [rbp-0x48]
000006A0  58                pop rax
000006A1  5B                pop rbx
000006A2  480FAFC3          imul rax,rbx
000006A6  50                push rax
000006A7  FF75A8            push qword [rbp-0x58]
000006AA  49BF000000000000  mov r15,0x0
         -0000
000006B4  4157              push r15
000006B6  58                pop rax
000006B7  5B                pop rbx
000006B8  4801D8            add rax,rbx
000006BB  50                push rax
000006BC  49BF020000000000  mov r15,0x2
         -0000
000006C6  4157              push r15
000006C8  FF75C0            push qword [rbp-0x40]
000006CB  58                pop rax
000006CC  5B                pop rbx
000006CD  480FAFC3          imul rax,rbx
000006D1  50                push rax
000006D2  58                pop rax
000006D3  5B                pop rbx
000006D4  48F7FB            idiv rbx
000006D7  50                push rax
000006D8  8F45A0            pop qword [rbp-0x60]
000006DB  49BFFFFFFFFFFFFF  mov r15,0xffffffffffffffff
         -FFFF
000006E5  4157              push r15
000006E7  FF75B8            push qword [rbp-0x48]
000006EA  58                pop rax
000006EB  5B                pop rbx
000006EC  480FAFC3          imul rax,rbx
000006F0  50                push rax
000006F1  FF75A8            push qword [rbp-0x58]
000006F4  49BF000000000000  mov r15,0x0
         -0000
000006FE  4157              push r15
00000700  58                pop rax
00000701  5B                pop rbx
00000702  4829D8            sub rax,rbx
00000705  50                push rax
00000706  49BF020000000000  mov r15,0x2
         -0000
00000710  4157              push r15
00000712  FF75C0            push qword [rbp-0x40]
00000715  58                pop rax
00000716  5B                pop rbx
00000717  480FAFC3          imul rax,rbx
0000071B  50                push rax
0000071C  58                pop rax
0000071D  5B                pop rbx
0000071E  48F7FB            idiv rbx
00000721  50                push rax
00000722  8F4598            pop qword [rbp-0x68]
00000725  FF75C0            push qword [rbp-0x40]
00000728  49BF000000000000  mov r15,0x0
         -0000
00000732  4157              push r15
00000734  5B                pop rbx
00000735  58                pop rax
00000736  4839D8            cmp rax,rbx
00000739  0F847B000000      jz near 0x7ba
0000073F  FF75A8            push qword [rbp-0x58]
00000742  49BF000000000000  mov r15,0x0
         -0000
0000074C  4157              push r15
0000074E  5B                pop rbx
0000074F  58                pop rax
00000750  4839D8            cmp rax,rbx
00000753  0F8312000000      jnc near 0x76b
00000759  49BF6A0401000000  mov r15,0x1046a
         -0000
00000763  4157              push r15
00000765  58                pop rax
00000766  E88DF9FFFF        call 0xf8
0000076B  FF75A8            push qword [rbp-0x58]
0000076E  49BF000000000000  mov r15,0x0
         -0000
00000778  4157              push r15
0000077A  5B                pop rbx
0000077B  58                pop rax
0000077C  4839D8            cmp rax,rbx
0000077F  0F8509000000      jnz near 0x78e
00000785  FF75A0            push qword [rbp-0x60]
00000788  58                pop rax
00000789  E86AF9FFFF        call 0xf8
0000078E  FF75A8            push qword [rbp-0x58]
00000791  49BF000000000000  mov r15,0x0
         -0000
0000079B  4157              push r15
0000079D  5B                pop rbx
0000079E  58                pop rax
0000079F  4839D8            cmp rax,rbx
000007A2  0F8E12000000      jng near 0x7ba
000007A8  FF75A0            push qword [rbp-0x60]
000007AB  58                pop rax
000007AC  E847F9FFFF        call 0xf8
000007B1  FF7598            push qword [rbp-0x68]
000007B4  58                pop rax
000007B5  E83EF9FFFF        call 0xf8
000007BA  FF75C0            push qword [rbp-0x40]
000007BD  49BF000000000000  mov r15,0x0
         -0000
000007C7  4157              push r15
000007C9  5B                pop rbx
000007CA  58                pop rax
000007CB  4839D8            cmp rax,rbx
000007CE  0F85B1000000      jnz near 0x885
000007D4  FF75B8            push qword [rbp-0x48]
000007D7  49BF000000000000  mov r15,0x0
         -0000
000007E1  4157              push r15
000007E3  5B                pop rbx
000007E4  58                pop rax
000007E5  4839D8            cmp rax,rbx
000007E8  0F8558000000      jnz near 0x846
000007EE  FF75B0            push qword [rbp-0x50]
000007F1  49BF000000000000  mov r15,0x0
         -0000
000007FB  4157              push r15
000007FD  5B                pop rbx
000007FE  58                pop rax
000007FF  4839D8            cmp rax,rbx
00000802  0F8512000000      jnz near 0x81a
00000808  49BF385B01000000  mov r15,0x15b38
         -0000
00000812  4157              push r15
00000814  58                pop rax
00000815  E8DEF8FFFF        call 0xf8
0000081A  FF75B0            push qword [rbp-0x50]
0000081D  49BF000000000000  mov r15,0x0
         -0000
00000827  4157              push r15
00000829  5B                pop rbx
0000082A  58                pop rax
0000082B  4839D8            cmp rax,rbx
0000082E  0F8412000000      jz near 0x846
00000834  49BFA9FBFFFFFFFF  mov r15,0xfffffffffffffba9
         -FFFF
0000083E  4157              push r15
00000840  58                pop rax
00000841  E8B2F8FFFF        call 0xf8
00000846  FF75B8            push qword [rbp-0x48]
00000849  49BF000000000000  mov r15,0x0
         -0000
00000853  4157              push r15
00000855  5B                pop rbx
00000856  58                pop rax
00000857  4839D8            cmp rax,rbx
0000085A  0F8425000000      jz near 0x885
00000860  49BFFFFFFFFFFFFF  mov r15,0xffffffffffffffff
         -FFFF
0000086A  4157              push r15
0000086C  FF75B0            push qword [rbp-0x50]
0000086F  FF75B8            push qword [rbp-0x48]
00000872  58                pop rax
00000873  5B                pop rbx
00000874  48F7FB            idiv rbx
00000877  50                push rax
00000878  58                pop rax
00000879  5B                pop rbx
0000087A  480FAFC3          imul rax,rbx
0000087E  50                push rax
0000087F  58                pop rax
00000880  E873F8FFFF        call 0xf8
00000885  B801000000        mov eax,0x1
0000088A  BB00000000        mov ebx,0x0
0000088F  CD80              int 0x80

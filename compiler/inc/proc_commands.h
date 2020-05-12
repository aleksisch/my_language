#define VAR_POP(tmp) elem_t tmp = 0; stack_pop (&(processor->cpu_stack), &tmp);
#define PUSH_STACK(tmp)    stack_push(&(processor->cpu_stack), (tmp));

DEF(PUSH, ELEM_T,
   {
        PUSH_STACK(*((elem_t*) (asm_text + counter_byte)));

        counter_byte += size_elem_t;
   })

DEF(ADD, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 + tmp2);
    })

DEF(MUL, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 * tmp2);
    })

DEF(SUB, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp2 - tmp1);
    })

DEF(DIV, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp2 / tmp1);
    })

DEF(PUSH, REG,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += size_elem_t;

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        if (ptr_reg == nullptr)
            printf("bad register error in PUSH register");

        PUSH_STACK(*ptr_reg);
    })

DEF(POP, REG,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += size_elem_t;

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        if (ptr_reg == nullptr)
            printf("bad register error in pop from register");

        stack_pop(&(processor->cpu_stack), ptr_reg);
    })

DEF(IN, NO_ARG,
    {
        elem_t tmp = 0;

        scanf(CONST_FOR_ELEM_T, &tmp);

        PUSH_STACK(tmp);
    })

DEF(OUT, NO_ARG,
    {
        VAR_POP(tmp);

        printf(CONST_FOR_ELEM_T "\n", tmp);
    })

DEF(SQRT, NO_ARG,
    {
        VAR_POP(tmp);

        PUSH_STACK(sqrt(tmp));
    })


DEF(POW, NO_ARG,
    {
        VAR_POP(first);

        VAR_POP(second);

        PUSH_STACK(std::pow(second, first));    //PUSH second^first

    })

DEF(JMP, LABEL,
    {
        counter_byte = (int) *((elem_t*) (asm_text + counter_byte));
    })

DEF(JA, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (first - second > 0)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(JAE, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (fabs(first - second) <= (elem_t) EPSILON)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(JNE, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (fabs(first - second) >= (elem_t) EPSILON)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(JE, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (fabs(first - second) <= (elem_t) EPSILON)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(JLE, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (second <= first)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(JL, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (second < first)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(JME, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (second >= first)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(JM, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (second > first)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += size_elem_t;
    })

DEF(END, NO_ARG,
    {
        counter_byte = size_bin;
    })     //to end running program

DEF(PUSH, RAM,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += size_elem_t;

        PUSH_STACK(processor->RAM[cmd % RAM_LENGTH]);
    })

DEF(POP, RAM,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += size_elem_t;

        VAR_POP(temp);

        if (cmd > RAM_LENGTH) printf("OVERFLOW IN RAM\n");

        processor->RAM[cmd % RAM_LENGTH] = temp;
    })

DEF(PUSH, (RAM | REG),
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += size_elem_t;

        elem_t* reg = get_reg_num(cmd, processor);

        if (reg == nullptr || *reg > RAM_LENGTH) printf("OWERFLOW IN RAM || bad register");

        else stack_push(&(processor->cpu_stack), (processor->RAM)[((int)*reg) % RAM_LENGTH]);
    })

DEF(POP, (RAM | REG),
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += size_elem_t;

        elem_t* reg =  get_reg_num(cmd, processor);

        if (reg ==  nullptr || (int) *reg > RAM_LENGTH) printf("OWERFLOW IN RAM || nullptr\n");

        else stack_pop(&(processor->cpu_stack), processor->RAM + ( ((int) *reg) % RAM_LENGTH) );
    })

DEF(CALL, LABEL,
    {
        stack_push(&(processor->func_stack), (elem_t) counter_byte);

        counter_byte = (int) *((elem_t*) (asm_text + counter_byte));
    })

DEF(RET, NO_ARG,
    {
        elem_t stk = 0;

        stack_pop(&(processor->func_stack), &stk);

        counter_byte = (int) stk + size_elem_t;
    })

DEF(DUMP, NO_ARG,
    {
        stack_dump(&(processor->cpu_stack));
    })

DEF(MEOW, NO_ARG,
    {
        printf("this is a cat\n");
    })

#undef VAR_POP
#undef PUSH_STACK

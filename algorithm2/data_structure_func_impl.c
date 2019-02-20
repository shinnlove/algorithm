//
// Created by shinnlove on 2019-02-20.
//

#include <stdio.h>
#include <mm_malloc.h>
#include "data_structure_func.h"

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

/**
 * 初始化空栈。
 *
 * @param sp
 * @return
 */
Status initStack(SqStackPoint sp) {
    // 构造一个空栈：让base指针指向`SElemType`数组
    sp->base = (SElemType *) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!sp->base) {
        exit(OVERFLOW);
    }

    sp->top = sp->base;

    sp->stack_size = STACK_INIT_SIZE;

    return OK;
}

/**
 * 栈是否为空，若空返回true，否则返回false。
 *
 * @param s
 * @return
 */
Status stackEmpty(SqStack s) {
    if (s.top == s.base) {
        return TRUE;
    }
    return FALSE;
}

/**
 * 获取栈顶元素。
 *
 * getTop自身返回是否成功，那么把元素类型的引用传进来(地址)，间接寻址后得到元素值。
 *
 * @param s
 * @param e
 * @return
 */
Status getTop(SqStack s, SElemType *e) {
    // 栈空
    if (s.top == s.base) {
        return ERROR;
    }

    *e = *(s.top - 1);

    return OK;
}

/**
 * 元素压栈。
 *
 * @param sp
 * @param e
 * @return
 */
Status push(SqStackPoint sp, SElemType e) {
    if (sp->top - sp->base >= sp->stack_size) {
        // 栈满，追加存储空间
        sp->base = (SElemType *) realloc(sp->base, (sp->stack_size + STACK_INCREMENT) * sizeof(SElemType));
        if (!sp->base) {
            exit(OVERFLOW);
        }
        // 重新定位栈顶指针
        sp->top = sp->base + sp->stack_size;
        // 容量扩容
        sp->stack_size += STACK_INCREMENT;
    }
    // 压栈元素
    *sp->top++ = e;

    return OK;
}

/**
 * 从栈弹出元素。
 *
 * 因为pop本身返回成功或失败，所以用元素的引用作为形参传入，这样间接寻址就可以得到其值。
 *
 * @param sp
 * @param e
 * @return
 */
Status pop(SqStackPoint sp, SElemType *e) {
    if (sp->top == sp->base) {
        return ERROR;
    }
    // 先自减才能拿到栈顶元素
    *e = *--sp->top;

    return OK;
}


/**
 * 递归创建一棵二叉树。
 *
 * 特别注意：
 *  起初的错误是：当递归调用创建二叉树时，形参传入的是根结点的lchild，一开始并没有初始化，所以内存地址不确定0x0000000....->记做地址1
 *  当输入左结点如36，此时开辟了一块内存地址给函数形参root指针，记做地址2；而外部传入的实参已经完成了拷贝，自身没有发生任何改变。
 *  当进入下一层递归、或者本层递归结束，新开辟的结点地址并没有赋值给根结点左右孩子，因此二叉树创建失败。
 *
 *  当进入下一层递归、要将新创建的结点挂到上一层左右子树上，即新结点地址给到上一层左右子树指针的值。
 *  但是因为函数形参是值拷贝，如果仅仅送入`root->lchild`，拷贝给它出了函数局部变量就释放了!!!
 *  因此关键就是将`root->lchild`的地址、即它的引用作为形参传入，
 *  创建新结点并把地址给到`root->lchild`，就是 `*root->lchild = 新结点地址`。
 *  开辟出来的空间本来就是一个地址，因此直接赋予即可。
 *
 *  总结：要修改某指针值就定义函数入参为指针的指针、实参传入的时候取该指针地址、在调用函数中修改地址时加上*取地址内值（即本指针的值）即可!!!
 *
 * @param root      上一层树的根结点地址的引用
 * @return          创建成功返回1
 */
Status createBiTree(BiTree *root) {

    printf("请按顺序输入二叉树的根结点，输入0代表空树或结束：\n");

    int data;
    scanf("%d", &data);


    if (data == 0) {
        *root = NULL;
    } else {
        // 为当前子树、新根、结点分配内存
        BiTree current = (BiTNode *) malloc(LEN);
        if (!current) {
            exit(OVERFLOW);
        }

        // !!!让形参指针内的地址指向本结点地址
        // 也就是让上一次的根节点地址指向自己
        *root = current;

        // 当前节点(自己作为根结点)赋值
        current->data = data;

        // 创建左子树
        createBiTree(&current->lchild);
        // 创建右子树
        createBiTree(&current->rchild);
    }
    return OK;
}

/**
 * 先根顺序遍历二叉树。
 *
 * @param tree      二叉树根结点指针
 * @param Visit     访问函数指针
 * @return
 */
Status preOrderTraverse(BiTree root, Status *(Visit)(TElemType e)) {
    // 空树
    if (!root) {
        return OK;
    }

    if (Visit(root->data)) {
        // 先根
        if (preOrderTraverse(root->lchild, Visit)) {
            // 再左孩子
            if (preOrderTraverse(root->rchild, Visit)) {
                // 再右孩子
                return OK;
            }
        }
    }

    // 其他一律没访问成功
    return ERROR;
}

/**
 * 树的中序遍历。
 *
 * 特别注意：这里栈压入的元素是树结点指针、或树根指针。
 * 于是操作push、pop、getTop都要看清楚，如果是元素、则直接就是指针；如果是指向元素的指针、就传入指针的地址!!!
 *
 * @param root
 * @param Visit
 * @return
 */
Status inOrderTraverse(BiTree root, Status *(Visit)(TElemType e)) {
    // 初始化辅助栈
    SqStack stack;
    SqStackPoint sp = &stack;
    initStack(sp);

    push(sp, root); // 根指针进栈

    // 中序遍历指针(当前访问位置)
    // 特别注意：getTop和pop都是要修改元素值，栈中存的是指针变量、而遍历游标是个要被修改的指针，所以这两个函数传入游标的地址。
    BiTree p;

    while (!stackEmpty(stack)) {

        // 下面这段代码对叶子结点会忽略(本来就是空指针直接pass)
        while (getTop(stack, &p) && p) {
            // 向左走到尽头(直到某左子树的左孩子为空指针)
            push(sp, p->lchild);
        }

        // 空指针退栈
        pop(sp, &p);

        if (!stackEmpty(stack)) {
            // 弹出准备访问的左子树元素、根元素、右子树元素
            // 第一次必定是左子树叶子结点、而后叶子节点右空指针被压进去、而后根节点被弹出、根节点右孩子被压进去
            // 而后就是有孩子的左子树第一个结点...如此必定把整个右孩子子树访问完毕
            pop(sp, &p);

            if (!Visit(p->data)) {
                return ERROR;
            }

            push(sp, p->rchild);

        } // if

    } // while
}

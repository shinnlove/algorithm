//
// Created by shinnlove on 2019-02-20.
//

#include <stdio.h>
#include <mm_malloc.h>
#include "data_structure_func.h"

/**
 * 访问一个元素，输出其值。
 *
 * @param e
 * @return
 */
Status visit(TElemType e) {
    printf("current visited: e=%d\n", e);
    return OK;
}

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
        BiTree current = (BiTNode *) malloc(BiTNodeLEN);
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
 * 递归型——树的中序遍历。
 *
 * 特别注意：这里栈压入的元素是树结点指针、或树根指针。
 * 于是操作push、pop、getTop都要看清楚，如果是元素、则直接就是指针；如果是指向元素的指针、就传入指针的地址!!!
 *
 * @param root
 * @param Visit
 * @return
 */
Status inOrderTraverseRecursive(BiTree root, Status *(Visit)(TElemType e)) {
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

/**
 * 非递归型树的中根遍历。
 *
 * @param root
 * @param Visit
 * @return
 */
Status inOrderTraverse(BiTree root, Status *(Visit)(TElemType e)) {
    // 初始化辅助栈
    SqStack stack;
    SqStackPoint sp = &stack;

    // 遍历指针(一开始指向根节点)
    BiTree p = root;

    while (p || !stackEmpty(stack)) {
        if (p) {
            // 根指针进栈、遍历左子树
            push(sp, p);
            p = p->lchild;
        } else {
            // p空可能：
            //  1.1 整棵树空
            //  1.2 是走到了左子树的叶子节点左孩子

            // 碰到空指针弹出一个压栈元素访问
            pop(sp, &p);

            if (!Visit(p->data)) {
                return ERROR;
            }

            // 访问这个结点的右孩子
            p = p->rchild;
        }
    } // while

    return OK;
}

/**
 * 后根顺序遍历二叉树。
 *
 * @param root
 * @param Visit
 * @return
 */
Status postOrderTraverseRecursive(BiTree root, Status *(Visit)(TElemType e)) {

    // 空树或某层递归遇到叶子节点
    if (root == NULL) {
        return OK;
    }

    // 递归访问左子树
    postOrderTraverseRecursive(root->lchild, Visit);

    // 递归访问右子树
    postOrderTraverseRecursive(root->rchild, Visit);

    // 后根访问自己
    Visit(root->data);

    return OK;

}

/**
 * 创建一颗可以被线索化的二叉树。
 *
 * @param root  线索二叉树的根结点指针
 * @return
 */
Status createBiThrTree(BiThrTree *root) {

    printf("请按顺序输入线索二叉树的根结点，输入0代表空树或结束：\n");

    int data;
    scanf("%d", &data);


    if (data == 0) {
        *root = NULL;
    } else {
        // 为当前子树、新根、结点分配内存
        BiThrTree current = (BiThrNode *) malloc(BiThrNodeLEN);
        if (!current) {
            exit(OVERFLOW);
        }

        // !!!让形参指针内的地址指向本结点地址
        // 也就是让上一次的根节点地址指向自己
        *root = current;

        // 当前节点(自己作为根结点)赋值
        current->data = data;

        // 创建线索左子树
        createBiThrTree(&current->lchild);
        // 创建线索右子树
        createBiThrTree(&current->rchild);
    }
    return OK;
}

/**
 * 对线索二叉树进行线索化
 *
 * @param tree      形参变量，进入函数后是指向`BiThrTree`类型的一个指针，初始化指向根结点指针。
 * @param root      原来指向根节点的指针
 * @return          线索化成功返回1
 */
Status inOrderThreading(BiThrTree *tree, BiThrTree root) {

    // 先建立线索化二叉树的头节点
    BiThrTree headNode = (BiThrNode *) malloc(BiThrNodeLEN);
    if (!headNode) {
        exit(OVERFLOW);
    }

    // 头结点挂到线索二叉树上
    *tree = headNode;

    // 头节点左孩子永远指向一颗非空树，因此是Link
    headNode->LTag = Link;

    // 头节点右孩子指向最后一个结点
    headNode->RTag = Thread;
    // 但如果线索化的是空树，头节点右指针就要指向自己!!后续线索化后会指向最后一个结点
    headNode->rchild = headNode;

    if (!root) {
        // 若二叉树空、头节点左子树指针回指
        headNode->lchild = headNode;
    } else {
        // 不空则线索化传入的这棵树
        headNode->lchild = root;

        // 线索化二叉树过程中经过的上个结点，是一个指向结点指针的游标
        // 初始化的时候指向线索头节点而不是二叉树的根
        BiThrTree pre = headNode;

        // 递归线索化、并不断改pre的值
        // 但是线索化是从树根开始的，头节点不进行线索化
        inThreading(&root, &pre);

        // 最后一个结点后继指回线索头节点
        pre->rchild = headNode;
        pre->RTag = Thread;

        // 头节点后继是最后一个结点
        headNode->rchild = pre;
    }

    return OK;
}

/**
 * 中序递归线索化二叉树。
 *
 * 其中`(*current)->lchild`就是当前要线索化结点的左孩子指针，
 * 再取&就是左孩子指针的地址，传入做下一次线索化的结点位置。
 *
 * @param current   线索化当前结点的指针，从根节点开始。
 * @param pre       线索化上一个结点的指针，从线索头结点开始，线索头结点左孩子指向根节点。
 */
void inThreading(BiThrTree *current, BiThrTree *pre) {
    if (*current) {

        // 线索化当前结点左子树
        // 此时不是`&((*pre)->rchild)`，因为递归到左子树叶子节点，此时前驱是头节点，所以pre不能动!!
        inThreading(&((*current)->lchild), pre);

        // 建立当前结点前驱线索->看当前结点的左孩子是否为空
        if (!(*current)->lchild) {
            // 当前结点没有左孩子，当前结点指向前驱(地址!!)
            (*current)->LTag = Thread;
            (*current)->lchild = *pre;
        }

        // 上一个结点后继线索->看上一个结点的右孩子是否为空
        if (!(*pre)->rchild) {
            // 先前结点没有右孩子，则先前结点的后继指向当前结点(地址!!)
            (*pre)->RTag = Thread;
            (*pre)->rchild = *current;
        }

        // 同步两者指针所指结点地址（切莫同步形参!!!）
        *pre = *current;

        // 线索化当前结点右子树
        inThreading(&((*current)->rchild), pre);

    } // if
}

/**
 * 中序遍历线索二叉树
 *
 * @param root      线索二叉树的头结点
 * @param Visit
 * @return
 */
Status inOrderTraverse_Thr(BiThrTree root, Status *(Visit)(TElemType e)) {
    // 当前遍历游标指针（初始位置不是根节点是头结点!!）
    BiThrTree p = root->lchild;

    // 空树、或线索二叉树遍历一圈后游标会回到线索头结点!
    while (p != root) {

        // 有左孩子一直往下走（最左下角的指针原来为空、现在它指向线索头结点且Thread类型）
        while (p->LTag == Link) {
            p = p->lchild;
        }

        // 此时p一定是最左子树的叶子节点
        // 或者是一个根节点没有左子树、指针指向前驱的结点（这种指针初始化指向线索头结点）
        if (!Visit(p->data)) {
            return ERROR;
        }

        // 左、中、右访问原来是弹出空指针再弹出根；现在变成直接访问线索得到根
        // `p->rchild != root`这个条件代表p是最后一个结点了
        // 这里主要是解决没有右子树的case!!!
        while (p->RTag == Thread && p->rchild != root) {
            p = p->rchild;
            Visit(p->data);
        }

        // 真正有右子树的、访问右子树，等到下一轮循环去visit
        p = p->rchild;

    } // while

    return OK;
} // inOrderTraverse_Thr

/**
 * 右旋处理AVL树。
 *
 * 对以*root为根的二叉排序树作右旋处理，处理之后root指向新的树根结点，即旋转处理之前的左子树根节点。
 *
 * 心诀：
 * 右旋——新根右挂老根左
 *
 * @param root
 */
void R_Rotate(BSTree *root) {
    // lc指向的*root的左子树根节点
    BSTree lc = (*root)->lchild;

    // lc的右子树挂接为*root的左子树
    (*root)->lchild = lc->rchild;

    // root指向新的根节点
    lc->rchild = (*root);
    (*root) = lc;
}

/**
 * 左旋处理AVL树。
 *
 * 对以*root为根的二叉排序树作左旋处理，处理之后root指向新的树根结点，即旋转处理之前的右子树根节点。
 *
 * 心诀：
 * 左旋——新根左挂老根右
 *
 * @param root
 */
void L_Rotate(BSTree *root) {
    // rc指向的*root的右子树根节点
    BSTree rc = (*root)->rchild;

    // rc的左子树挂接为*root的右子树
    (*root)->rchild = rc->lchild;

    // root指向新的根节点
    rc->lchild = (*root);
    (*root) = rc;
}

/**
 * AVL调整左子树
 *
 * 对以指针root所指结点为根的二叉树做平衡旋转处理，本算法结束时，指针root指向新的根节点。
 *
 * 心诀：
 * 左平衡左子树左高插在左、左左单右旋、新根右挂老根左；
 * 左平衡左子树右高插在右、左右左右旋、左挂右来右挂左；
 *
 * @param root
 */
void leftBalance(BSTree *root) {
    // 口号：进入左处理函数一个"左"
    BSTree lc = (*root)->lchild;
    BSTree rd;
    switch (lc->bf) {
        case LH:
            // 左高：口号"左+左=>右"
            (*root)->bf = lc->bf = EH;
            R_Rotate(root);
            break;
        case RH:
            // 右高：口号"左+右=>左+右"
            rd = lc->rchild;
            switch (rd->bf) {
                case LH:
                    (*root)->bf = RH;
                    lc->bf = EH;
                    break;
                case EH:
                    (*root)->bf = lc->bf = EH;
                    break;
                case RH:
                    (*root)->bf = EH;
                    lc->bf = LH;
                    break;
            } // switch(rd->bf)

            rd->bf = EH;

            // 对*root的左子树作左旋平衡处理、左的是左孩子结点!
            L_Rotate((*root)->lchild);

            // 对*root做右旋平衡处理、右的是自己!
            R_Rotate((*root));

    } // switch (lc->bf)
}

/**
 * AVL调整右子树
 *
 * 对以指针root所指结点为根的二叉树做平衡旋转处理，本算法结束时，指针root指向新的根节点。
 *
 * 心诀：
 * 右平衡右子树右高插在右、右右单左旋、新根左挂老根右；
 * 右平衡右子树左高插在左、右左右左旋、右挂左来左挂右。
 *
 * @param root
 */
void rightBalance(BSTree *root) {
    // 口号：进入右处理函数一个"右"
    BSTree rc = (*root)->rchild;
    BSTree ld;
    switch (rc->bf) {
        case LH:
            // 左高：口号"右+左=>右+左"
            ld = rc->lchild;
            switch (ld->bf) {
                case LH:
                    (*root)->bf = EH;
                    ld->bf = LH;
                    break;
                case EH:
                    (*root)->bf = ld->bf = EH;
                    break;
                case RH:
                    (*root)->bf = RH;
                    ld->bf = EH;
                    break;
            } // switch(rd->bf)

            ld->bf = EH;

            // 对*root的右子树作右旋平衡处理、右的是右孩子结点!
            R_Rotate((*root)->rchild);

            // 对*root做左旋平衡处理、左的是自己!
            L_Rotate((*root));

        case RH:
            // 右高：口号"右+右=>左"
            (*root)->bf = ld->bf = EH;
            L_Rotate(root);
            break;

    } // switch (lc->bf)
}

/**
 * 插入调整AVL树
 *
 * AVL平衡调整心诀：
 * 新叶结点树长高，左右平衡是NULL；
 * 小插左，大插右，插入长高调平衡；
 * 左子树右高拉平衡、左子树平衡变左高、左子树左高左平衡；
 * 右子树左高拉平衡、右子树平衡变右高、右子树右高右平衡；
 * 左平衡左子树左高插在左、左左单右旋、新根右挂老根左；
 * 左平衡左子树右高插在右、左右左右旋、左挂右来右挂左；
 * 右平衡右子树右高插在右、右右单左旋、新根左挂老根右；
 * 右平衡右子树左高插在左、右左右左旋、右挂左来左挂右。
 *
 * @param root
 * @param e
 * @param taller
 * @return
 */
Status insertAVL(BSTree *root, TElemType e, Boolean *taller) {

    if (!(*root)) {
        // 树不存在，插入新根结点、树长高
        // 这个分支处理：根节点、左右孩子作为根节点的新树，是递归调用的结束分支!

        // 心诀："新叶结点树长高，左右平衡是NULL"
        (*root) = (BSTree) malloc(BSTNodeLEN);
        (*root)->data = e;
        (*root)->lchild = (*root)->rchild = NULL;
        (*root)->bf = EH;
        *taller = TRUE;
    } else {
        // 根节点存在

        if (e == (*root)->data) {
            // e == data
            *taller = FALSE;
            return FALSE;
        } else if (e < (*root)->data) {
            // e < data，插入在左子树上进行

            // 未插入
            if (!insertAVL((*root)->lchild, e, taller)) return FALSE;

            // 已插入
            if (*taller) {
                // 已插入到左子树中且左子树长高
                // 心诀：插入长高调平衡
                switch ((*root)->bf) {
                    case LH:
                        // 心诀：左子树左高左平衡
                        leftBalance(*root);
                        *taller = FALSE;
                        break;
                    case EH:
                        // 心诀：左子树平衡变左高
                        (*root)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH:
                        // 心诀：左子树右高变平衡
                        (*root)->bf = EH;
                        *taller = FALSE;
                        break;
                } // switch ((*root)->bf)
            } // if (*taller)

        } else {
            // e > data，插入在右子树上进行

            // 未插入
            if (!insertAVL((*root)->rchild, e, taller)) return FALSE;

            // 已插入
            if (*taller) {
                // 已插入到右子树中且右子树长高
                // 心诀：插入长高调平衡
                switch ((*root)->bf) {
                    case LH:
                        // 心诀：右子树左高变平衡
                        (*root)->bf = EH;
                        *taller = FALSE;
                        break;
                    case EH:
                        // 心诀：右子树平衡变右高
                        (*root)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH:
                        // 心诀：右子树右高右平衡
                        rightBalance(*root);
                        *taller = FALSE;
                        break;

                } // switch ((*root)->bf)
            } // if (*taller)

        } // else

    } // else


    return TRUE;
}

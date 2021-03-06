///  HW3.CPP
///
///  EEE456 Electromagnetic Modelling
///  1st June 2021
///
///  Group 1 - Homework 3
///
/// 161110004 - Onur AKSOY
/// 161110057 - Mine Nur ÖZER
/// 161110070 - Muhammed Halit TOKLUOĞLU

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** matrix(int N, int M);
void free_matrix(double** q);
void cgm(double **A, double *B, double *X, int N, int ITMAX, double TOL,double *AX);

int main()
{
    FILE *ToF;
    const int ne=144; // total number of elements
    const int n1=36; // number of nodes on Gamma_1 (Dirichlet boundary condition)
    const int nn=91; // total number of nodes (global)

    int ITMAX=100;
    double TOL=1E-6;
    int e,i,j;      // temporary variables
    int n[4][ne+1]; // n(i,e):connectivity array
                    // i:local number of a node
                    // e:element number
                    // n(i,e):global number of the node
    int nd[n1+1];   // global node numbers corresponding to Gamma_1
    double p[n1+1];
    double x[nn+1],y[nn+1]; // coordinates of global node numbers
    double **K;     // K[nn+1][nn+1]; // global matrix
    double b[nn+1];
    double X[nn+1];
    double AX[nn+1]; // Solution matrix; AX is not necessary
    double Ke[4][4]; // elemental matrix
    double be[4], ce[4];
    double deltae;

    K=matrix(nn+1,nn+1);

/// Input x and y coordinates of global node numbers
    x[1]=0.0;       y[1]=0.0;
    x[2]=1.0;       y[2]=-1.0;
    x[3]=2.0;       y[3]=-2.0;
    x[4]=3.0;       y[4]=-3.0;
    x[5]=4.0;       y[5]=-4.0;
    x[6]=5.0;       y[6]=-5.0;
    x[7]=6.0;       y[7]=-6.0;
    x[8]=7.0;       y[8]=-7.0;
    x[9]=8.0;       y[9]=-8.0;
    x[10]=9.0;      y[10]=-9.0;
    x[11]=10.0;     y[11]=-10.0;
    x[12]=11.0;     y[12]=-11.0;
    x[13]=12.0;     y[13]=-12.0;
    x[14]=11.0;     y[14]=-12.0;
    x[15]=10.0;     y[15]=-12.0;
    x[16]=9.0;      y[16]=-12.0;
    x[17]=8.0;      y[17]=-12.0;
    x[18]=7.0;      y[18]=-12.0;
    x[19]=6.0;      y[19]=-12.0;
    x[20]=5.0;      y[20]=-12.0;
    x[21]=4.0;      y[21]=-12.0;
    x[22]=3.0;      y[22]=-12.0;
    x[23]=2.0;      y[23]=-12.0;
    x[24]=1.0;      y[24]=-12.0;
    x[25]=0.0;      y[25]=-12.0;
    x[26]=0.0;      y[26]=-11.0;
    x[27]=0.0;      y[27]=-10.0;
    x[28]=0.0;      y[28]=-9.0;
    x[29]=0.0;      y[29]=-8.0;
    x[30]=0.0;      y[30]=-7.0;
    x[31]=0.0;      y[31]=-6.0;
    x[32]=0.0;      y[32]=-5.0;
    x[33]=0.0;      y[33]=-4.0;
    x[34]=0.0;      y[34]=-3.0;
    x[35]=0.0;      y[35]=-2.0;
    x[36]=0.0;      y[36]=-1.0;
    x[37]=1.0;      y[37]=-2.0;
    x[38]=1.0;      y[38]=-3.0;
    x[39]=2.0;      y[39]=-3.0;
    x[40]=1.0;      y[40]=-4.0;
    x[41]=2.0;      y[41]=-4.0;
    x[42]=3.0;      y[42]=-4.0;
    x[43]=1.0;      y[43]=-5.0;
    x[44]=2.0;      y[44]=-5.0;
    x[45]=3.0;      y[45]=-5.0;
    x[46]=4.0;      y[46]=-5.0;
    x[47]=1.0;      y[47]=-6.0;
    x[48]=2.0;      y[48]=-6.0;
    x[49]=3.0;      y[49]=-6.0;
    x[50]=4.0;      y[50]=-6.0;
    x[51]=5.0;      y[51]=-6.0;
    x[52]=1.0;      y[52]=-7.0;
    x[53]=2.0;      y[53]=-7.0;
    x[54]=3.0;      y[54]=-7.0;
    x[55]=4.0;      y[55]=-7.0;
    x[56]=5.0;      y[56]=-7.0;
    x[57]=6.0;      y[57]=-7.0;
    x[58]=1.0;      y[58]=-8.0;
    x[59]=2.0;      y[59]=-8.0;
    x[60]=3.0;      y[60]=-8.0;
    x[61]=4.0;      y[61]=-8.0;
    x[62]=5.0;      y[62]=-8.0;
    x[63]=6.0;      y[63]=-8.0;
    x[64]=7.0;      y[64]=-8.0;
    x[65]=1.0;      y[65]=-9.0;
    x[66]=2.0;      y[66]=-9.0;
    x[67]=3.0;      y[67]=-9.0;
    x[68]=4.0;      y[68]=-9.0;
    x[69]=5.0;      y[69]=-9.0;
    x[70]=6.0;      y[70]=-9.0;
    x[71]=7.0;      y[71]=-9.0;
    x[72]=8.0;      y[72]=-9.0;
    x[73]=1.0;      y[73]=-10.0;
    x[74]=2.0;      y[74]=-10.0;
    x[75]=3.0;      y[75]=-10.0;
    x[76]=4.0;      y[76]=-10.0;
    x[77]=5.0;      y[77]=-10.0;
    x[78]=6.0;      y[78]=-10.0;
    x[79]=7.0;      y[79]=-10.0;
    x[80]=8.0;      y[80]=-10.0;
    x[81]=9.0;      y[81]=-10.0;
    x[82]=1.0;      y[82]=-11.0;
    x[83]=2.0;      y[83]=-11.0;
    x[84]=3.0;      y[84]=-11.0;
    x[85]=4.0;      y[85]=-11.0;
    x[86]=5.0;      y[86]=-11.0;
    x[87]=6.0;      y[87]=-11.0;
    x[88]=7.0;      y[88]=-11.0;
    x[89]=8.0;      y[89]=-11.0;
    x[90]=9.0;      y[90]=-11.0;
    x[91]=10.0;     y[91]=-11.0;


/// Input n(i,e):connectivity array
    n[1][1]=36;     n[2][1]=2;	    n[3][1]=1;
    n[1][2]=35;     n[2][2]=37;	    n[3][2]=36;
    n[1][3]=37;     n[2][3]=2;	    n[3][3]=36;
    n[1][4]=37;     n[2][4]=3;	    n[3][4]=2;
    n[1][5]=34;     n[2][5]=38;	    n[3][5]=35;
    n[1][6]=38;     n[2][6]=37;	    n[3][6]=35;
    n[1][7]=38;     n[2][7]=39;	    n[3][7]=37;
    n[1][8]=39;     n[2][8]=3;	    n[3][8]=37;
    n[1][9]=39;     n[2][9]=4;	    n[3][9]=3;
    n[1][10]=33;    n[2][10]=40;    n[3][10]=34;
    n[1][11]=40;    n[2][11]=38;    n[3][11]=34;
    n[1][12]=40;    n[2][12]=41;    n[3][12]=38;
    n[1][13]=41;    n[2][13]=39;    n[3][13]=38;
    n[1][14]=41;    n[2][14]=42;    n[3][14]=39;
    n[1][15]=42;    n[2][15]=4;     n[3][15]=39;
    n[1][16]=42;    n[2][16]=5;     n[3][16]=4;
    n[1][17]=32;    n[2][17]=43;    n[3][17]=33;
    n[1][18]=43;    n[2][18]=40;    n[3][18]=33;
    n[1][19]=43;    n[2][19]=44;    n[3][19]=40;
    n[1][20]=44;    n[2][20]=41;    n[3][20]=40;
    n[1][21]=44;    n[2][21]=45;    n[3][21]=41;
    n[1][22]=45;    n[2][22]=42;    n[3][22]=41;
    n[1][23]=45;    n[2][23]=46;    n[3][23]=42;
    n[1][24]=46;    n[2][24]=5;     n[3][24]=42;
    n[1][25]=46;    n[2][25]=6;     n[3][25]=5;
    n[1][26]=31;    n[2][26]=47;    n[3][26]=32;
    n[1][27]=47;    n[2][27]=43;    n[3][27]=32;
    n[1][28]=47;    n[2][28]=48;    n[3][28]=43;
    n[1][29]=48;    n[2][29]=44;    n[3][29]=43;
    n[1][30]=48;    n[2][30]=49;    n[3][30]=44;
    n[1][31]=49;    n[2][31]=45;    n[3][31]=44;
    n[1][32]=49;    n[2][32]=50;    n[3][32]=45;
    n[1][33]=50;    n[2][33]=46;    n[3][33]=45;
    n[1][34]=50;    n[2][34]=51;    n[3][34]=46;
    n[1][35]=51;    n[2][35]=6;     n[3][35]=46;
    n[1][36]=51;    n[2][36]=7;     n[3][36]=6;
    n[1][37]=30;    n[2][37]=52;    n[3][37]=31;
    n[1][38]=52;    n[2][38]=47;    n[3][38]=31;
    n[1][39]=52;    n[2][39]=53;    n[3][39]=47;
    n[1][40]=53;    n[2][40]=48;    n[3][40]=47;
    n[1][41]=53;    n[2][41]=54;    n[3][41]=48;
    n[1][42]=54;    n[2][42]=49;    n[3][42]=48;
    n[1][43]=54;    n[2][43]=55;    n[3][43]=49;
    n[1][44]=55;    n[2][44]=50;    n[3][44]=49;
    n[1][45]=55;    n[2][45]=56;    n[3][45]=50;
    n[1][46]=56;    n[2][46]=51;    n[3][46]=50;
    n[1][47]=56;    n[2][47]=57;    n[3][47]=51;
    n[1][48]=57;    n[2][48]=7;     n[3][48]=51;
    n[1][49]=57;    n[2][49]=8;     n[3][49]=7;
    n[1][50]=29;    n[2][50]=58;    n[3][50]=30;
    n[1][51]=58;    n[2][51]=52;    n[3][51]=30;
    n[1][52]=58;    n[2][52]=59;    n[3][52]=52;
    n[1][53]=59;    n[2][53]=53;    n[3][53]=52;
    n[1][54]=59;    n[2][54]=60;    n[3][54]=53;
    n[1][55]=60;    n[2][55]=54;    n[3][55]=53;
    n[1][56]=60;    n[2][56]=61;    n[3][56]=54;
    n[1][57]=61;    n[2][57]=55;    n[3][57]=54;
    n[1][58]=61;    n[2][58]=62;    n[3][58]=55;
    n[1][59]=62;    n[2][59]=56;    n[3][59]=55;
    n[1][60]=62;    n[2][60]=63;    n[3][60]=56;
    n[1][61]=63;    n[2][61]=57;    n[3][61]=56;
    n[1][62]=63;    n[2][62]=64;    n[3][62]=57;
    n[1][63]=64;    n[2][63]=8;     n[3][63]=57;
    n[1][64]=64;    n[2][64]=9;     n[3][64]=8;
    n[1][65]=28;    n[2][65]=65;    n[3][65]=29;
    n[1][66]=65;    n[2][66]=58;    n[3][66]=29;
    n[1][67]=65;    n[2][67]=66;    n[3][67]=58;
    n[1][68]=66;    n[2][68]=59;    n[3][68]=58;
    n[1][69]=66;    n[2][69]=67;    n[3][69]=59;
    n[1][70]=67;    n[2][70]=60;    n[3][70]=59;
    n[1][71]=67;    n[2][71]=68;    n[3][71]=60;
    n[1][72]=68;    n[2][72]=61;    n[3][72]=60;
    n[1][73]=68;    n[2][73]=69;    n[3][73]=61;
    n[1][74]=69;    n[2][74]=62;    n[3][74]=61;
    n[1][75]=69;    n[2][75]=70;    n[3][75]=62;
    n[1][76]=70;    n[2][76]=63;    n[3][76]=62;
    n[1][77]=70;    n[2][77]=71;    n[3][77]=63;
    n[1][78]=71;    n[2][78]=64;    n[3][78]=63;
    n[1][79]=71;    n[2][79]=72;    n[3][79]=64;
    n[1][80]=72;    n[2][80]=9;     n[3][80]=64;
    n[1][81]=72;    n[2][81]=10;    n[3][81]=9;
    n[1][82]=27;    n[2][82]=73;    n[3][82]=28;
    n[1][83]=73;    n[2][83]=65;    n[3][83]=28;
    n[1][84]=73;    n[2][84]=74;    n[3][84]=65;
    n[1][85]=74;    n[2][85]=66;    n[3][85]=65;
    n[1][86]=74;    n[2][86]=75;    n[3][86]=66;
    n[1][87]=75;    n[2][87]=67;    n[3][87]=66;
    n[1][88]=75;    n[2][88]=76;    n[3][88]=67;
    n[1][89]=76;    n[2][89]=68;    n[3][89]=67;
    n[1][90]=76;    n[2][90]=77;    n[3][90]=68;
    n[1][91]=77;    n[2][91]=69;    n[3][91]=68;
    n[1][92]=77;    n[2][92]=78;    n[3][92]=69;
    n[1][93]=78;    n[2][93]=70;    n[3][93]=69;
    n[1][94]=78;    n[2][94]=79;    n[3][94]=70;
    n[1][95]=79;    n[2][95]=71;    n[3][95]=70;
    n[1][96]=79;    n[2][96]=80;    n[3][96]=71;
    n[1][97]=80;    n[2][97]=72;    n[3][97]=71;
    n[1][98]=80;    n[2][98]=81;    n[3][98]=72;
    n[1][99]=81;    n[2][99]=10;    n[3][99]=72;
    n[1][100]=81;   n[2][100]=11;   n[3][100]=10;
    n[1][101]=26;   n[2][101]=82;   n[3][101]=27;
    n[1][102]=82;   n[2][102]=73;   n[3][102]=27;
    n[1][103]=82;   n[2][103]=83;   n[3][103]=73;
    n[1][104]=83;   n[2][104]=74;   n[3][104]=73;
    n[1][105]=83;   n[2][105]=84;   n[3][105]=74;
    n[1][106]=84;   n[2][106]=75;   n[3][106]=74;
    n[1][107]=84;   n[2][107]=85;   n[3][107]=75;
    n[1][108]=85;   n[2][108]=76;   n[3][108]=75;
    n[1][109]=85;   n[2][109]=86;   n[3][109]=76;
    n[1][110]=86;   n[2][110]=77;   n[3][110]=76;
    n[1][111]=86;   n[2][111]=87;   n[3][111]=77;
    n[1][112]=87;   n[2][112]=78;   n[3][112]=77;
    n[1][113]=87;   n[2][113]=88;   n[3][113]=78;
    n[1][114]=88;   n[2][114]=79;   n[3][114]=78;
    n[1][115]=88;   n[2][115]=89;   n[3][115]=79;
    n[1][116]=89;   n[2][116]=80;   n[3][116]=79;
    n[1][117]=89;   n[2][117]=90;   n[3][117]=80;
    n[1][118]=90;   n[2][118]=81;   n[3][118]=80;
    n[1][119]=90;   n[2][119]=91;   n[3][119]=81;
    n[1][120]=91;   n[2][120]=11;   n[3][120]=81;
    n[1][121]=91;   n[2][121]=12;   n[3][121]=11;
    n[1][122]=25;   n[2][122]=24;   n[3][122]=26;
    n[1][123]=24;   n[2][123]=82;   n[3][123]=26;
    n[1][124]=24;   n[2][124]=23;   n[3][124]=82;
    n[1][125]=23;   n[2][125]=83;   n[3][125]=82;
    n[1][126]=23;   n[2][126]=22;   n[3][126]=83;
    n[1][127]=22;   n[2][127]=84;   n[3][127]=83;
    n[1][128]=22;   n[2][128]=21;   n[3][128]=84;
    n[1][129]=21;   n[2][129]=85;   n[3][129]=84;
    n[1][130]=21;   n[2][130]=20;   n[3][130]=85;
    n[1][131]=20;   n[2][131]=86;   n[3][131]=85;
    n[1][132]=20;   n[2][132]=19;   n[3][132]=86;
    n[1][133]=19;   n[2][133]=87;   n[3][133]=86;
    n[1][134]=19;   n[2][134]=18;   n[3][134]=87;
    n[1][135]=18;   n[2][135]=88;   n[3][135]=87;
    n[1][136]=18;   n[2][136]=17;   n[3][136]=88;
    n[1][137]=17;   n[2][137]=89;   n[3][137]=88;
    n[1][138]=17;   n[2][138]=16;   n[3][138]=89;
    n[1][139]=16;   n[2][139]=90;   n[3][139]=89;
    n[1][140]=16;   n[2][140]=15;   n[3][140]=90;
    n[1][141]=15;   n[2][141]=91;   n[3][141]=90;
    n[1][142]=15;   n[2][142]=14;   n[3][142]=91;
    n[1][143]=14;   n[2][143]=12;   n[3][143]=91;
    n[1][144]=14;   n[2][144]=13;   n[3][144]=12;


/// Input boundary conditions on Gamma_1
    nd[1]=1;        p[1]=20.0;
    nd[2]=2;        p[2]=10.0;
    nd[3]=3;        p[3]=10.0;
    nd[4]=4;        p[4]=10.0;
    nd[5]=5;        p[5]=10.0;
    nd[6]=6;        p[6]=10.0;
    nd[7]=7;        p[7]=10.0;
    nd[8]=8;        p[8]=10.0;
    nd[9]=9;        p[9]=10.0;
    nd[10]=10;      p[10]=10.0;
    nd[11]=11;      p[11]=10.0;
    nd[12]=12;      p[12]=10.0;
    nd[13]=13;      p[13]=10.0;
    nd[14]=14;      p[14]=0.0;
    nd[15]=15;      p[15]=0.0;
    nd[16]=16;      p[16]=0.0;
    nd[17]=17;      p[17]=0.0;
    nd[18]=18;      p[18]=0.0;
    nd[19]=19;      p[19]=0.0;
    nd[20]=20;      p[20]=0.0;
    nd[21]=21;      p[21]=0.0;
    nd[22]=22;      p[22]=0.0;
    nd[23]=23;      p[23]=0.0;
    nd[24]=24;      p[24]=0.0;
    nd[25]=25;      p[25]=0.0;
    nd[26]=26;      p[26]=20.0;
    nd[27]=27;      p[27]=20.0;
    nd[28]=28;      p[28]=20.0;
    nd[29]=29;      p[29]=20.0;
    nd[30]=30;      p[30]=20.0;
    nd[31]=31;      p[31]=20.0;
    nd[32]=32;      p[32]=20.0;
    nd[33]=33;      p[33]=20.0;
    nd[34]=34;      p[34]=20.0;
    nd[35]=35;      p[35]=20.0;
    nd[36]=36;      p[36]=20.0;
   

// Initialize matrix [K]
    for (i=1;i<=nn;i++) {
        for (j=1;j<=nn;j++) {
            K[i][j]=0.0;
        }
    }

// Initialize vector [b]
    for (i=1;i<=nn;i++) {
        b[i]=0.0;
    }

// Start to assemble all area elements in Omega
    for (e=1;e<=ne;e++) {
        // Calculate b^e_i and c^e_i (i=1,2,3)
        be[1]=y[n[2][e]]-y[n[3][e]];
        be[2]=y[n[3][e]]-y[n[1][e]];
        be[3]=y[n[1][e]]-y[n[2][e]];
        ce[1]=x[n[3][e]]-x[n[2][e]];
        ce[2]=x[n[1][e]]-x[n[3][e]];
        ce[3]=x[n[2][e]]-x[n[1][e]];

        // Calculate Delta^e
        deltae=0.5*(be[1]*ce[2]-be[2]*ce[1]);

        // Generate the elemental matrix [K^e]
        for (i=1;i<=3;i++) {
            for (j=1;j<=3;j++) {
                Ke[i][j]= (be[i]*be[j]+ce[i]*ce[j])/(4.0*deltae);
            }
        }

        // Add [K^e] to [K]
        for (i=1;i<=3;i++) {
            for (j=1;j<=3;j++) {
                K[n[i][e]][n[j][e]] += Ke[i][j];
            }
        }
    }

    // Impose the Dirichlet boundary condition
    for (i=1;i<=n1;i++) {
        b[nd[i]]=p[i];
        K[nd[i]][nd[i]]=1.0;
        for (j=1;j<=nn;j++) {
            if (j != nd[i]) {
                b[j] -= K[j][nd[i]]*p[i];
                K[nd[i]][j]=0.0;
                K[j][nd[i]]=0.0;
            }
        }
    }

    if ((ToF = fopen("fem.txt", "w")) == NULL) {
        printf("Error opening text file for writing\n");
        exit(0);
    }

    fprintf(ToF,"K matrix values\n");
    for (i=1;i<=nn;i++) {
        for (j=1;j<=nn;j++) {
            fprintf(ToF,"K[%d][%d]: %lf\n",i,j,K[i][j]);
        }
    }
    fprintf(ToF,"\n");

    fprintf(ToF,"Diagonal elements of K (must be different from zero)\n");
    for (i=1;i<=nn;i++) {
        fprintf(ToF,"K[%d][%d]: %lf\n",i,i,K[i][i]);
    }
    fprintf(ToF,"\n");

    fprintf(ToF,"b vector values\n");
    for (i=1;i<=nn;i++) {
        fprintf(ToF,"b[%d]: %lf\n",i,b[i]);
    }
    fprintf(ToF,"\n");

    cgm(K, b, X, nn, ITMAX, TOL, AX);

    fprintf(ToF,"X solution vector values\n");
    for (i=1;i<=nn;i++) {
        printf("X[%d]: %lf\n",i,X[i]);
        fprintf(ToF,"X[%d]: %lf\n",i,X[i]);
    }

    free_matrix(K);

    fclose(ToF);
    return(0);
}

void prod(double **A, double *X, double *AX, int control, int N);
double *alloc_vector(int N);
void free_vector(double *v);
double** matrix(int N, int M);
void free_matrix(double** q);
void cgm(double **A, double *B, double *X, int N, int ITMAX, double TOL,
double *AX);

double *alloc_vector(int N)
// allocates a double vector with range[0..(N-1)]
{
    double *v;
    v=new double [N];
    if (!v) {
        printf("Out of memory in alloc_vector\n");
        exit(1);
    }
    return(v);
} // of double *alloc_vector()

void free_vector(double *v)
// frees a double vector allocated by alloc_vector()
{
    delete v;
} // of void free_vector()

double** matrix(int N, int M)
// Allocates two-dimensional array q[0..(N-1)][0..(M-1)]
{
    double** q;
    int j;

    q = new double* [N];
    if(!q) {
        printf("Out of memory\n");
        exit(0);
    }

    for(j=0; j<N; j++) {
        q[j] = new double [M];
        if(!q[j]) {
            printf("Out of memory\n");
            exit(0);
        }
    }
    return(q);
} // of double** matrix()

void free_matrix(double** q)
{
    delete q;
}

double  vnorm(double *Z, int N)
// Z is [1..N] double vector
// Euclidan norm of a vector:|*|^2
{
    double sum, result;
    int i;

    sum=0.0;

    for (i=1; i<= N; i++) {
        sum += pow(Z[i], 2);
    }

    result=sum;
    return(result);
} // of double vnorm()

void prod(double **A, double *X, double *AX, int control, int N)
// Matrix-Vector Multiplication
{
    int i,j,k;

    for (i=1; i<=N; i++) {
        AX[i]=0.0;
    }

    if (control==1) { // * var
        for (k=1; k<=N; k++) {
            for (j=1; j<=N; j++) {
                AX[k] += A[j][k]*X[j];
            }
        }
    }
    else { // * yok
        for (j=1; j<=N; j++) {
            for (k=1; k<=N; k++) {
                AX[j] += A[j][k]*X[k];
            }
        }
    }
} // of void prod()

void cgm(double **A, double *B, double *X, int N, int ITMAX, double TOL, double *AX)
{
    double *R, *P;
    double vnrm, alpha, beta, RSS;
    int i, iter=0;

    P=alloc_vector(N+1);
    R=alloc_vector(N+1);

    vnrm=vnorm(B, N);
    for (i=1; i<=N; i++) {
        X[i]=0.0;
    }

    prod(A, X, AX, 0, N);

    for (i=1; i<=N;i++) {
        R[i]=B[i]-AX[i];
    }

    prod(A, R, AX, 1, N);
    beta=1.0/vnorm(AX,N);

    for (i=1; i<=N; i++) {
        P[i]=beta*AX[i];
    }

    while (iter <= ITMAX) {
        prod(A,P,AX,0,N);
        alpha=1.0/vnorm(AX,N);
        for (i=1; i<=N;i++) {
            X[i] = X[i]+alpha*P[i];
            R[i] = R[i]-alpha*AX[i];
        }

        prod(A,R,AX,1,N);
        beta=1.0/vnorm(AX,N);
        for (i=1; i<=N;i++) {
            P[i] += beta*AX[i];
        }
        iter++;
        printf("%d\n",iter);
        RSS=sqrt(vnorm(R,N)/vnrm);
        printf("%4d, %14.4lf\n",iter,RSS);
        if (RSS<=TOL) {
            printf("Convergence achieved\n");

            free_vector(R);
            free_vector(P);

            return;
        }
        else {
            if (iter==ITMAX) {
                printf("ITMAX exceeded. No convergence.\n");

                free_vector(R);
                free_vector(P);
                exit(0);
            }
        }
    }

    free_vector(R);
    free_vector(P);
    return;
} // of void cgm()

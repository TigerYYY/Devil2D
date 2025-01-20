//
//  devil2D-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//  Функция, которая генерирует датасет "Игрушка дьявола"
//  из N точек и K классов в 2-мерном пространстве.
//

#include <iostream>
#include <locale>
#include <vector>
#include <iomanip>
#include <cassert>
#include <random>

using namespace  std;

// Точка в 2D
struct Point2D
{
    // 
    double  x{0};
    // 
    double  y{0};
};

// 
int  devil2D( const int  N, const int  K, vector< Point2D >&  X, vector< unsigned char >&  y );

//# Добавим в данные шум, чтобы усложнить задачу.
//X[:, 0] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
//X[:, 1] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
int  Noise2D( vector< Point2D >&  X );

int main()
{
    setlocale( LC_ALL, "Rus" );

    // Кол-во точек
    int  N{0};
    cout << "Введите кол-во точек (N): ";   cin >> N;

    // Кол-во классов
    int  K{0};
    cout << "Кол-во классов точек (K): ";   cin >> K;

    // Координаты точек
    vector< Point2D >  X( N * K  );
    // Принадлежность точек классам: 0, 1, ... K - 1
    vector< unsigned char >  y( N * K, 0 );

    // Функция, которая генерирует датасет "Игрушка дьявола"
    // из N точек и K классов в 2-мерном пространстве.
    devil2D( N, K, X, y );

    cout << "\n";

    int l{0};
    for(int i = 0; i < K; ++i)
    {
        for( int j = 0 ; j < N ; ++j )
        {
            cout.width( 15 );
            cout.setf( ios::fixed | ios::right );
            cout.precision( 8 );
            cout << X[ l ].x << "\t";
            cout.width( 15 );
            cout.setf( ios::fixed | ios::right );
            cout.precision( 8 );
            cout << X[ l ].y << "\t";
            cout.width( 5 );
            cout.setf( ios::fixed | ios::right );
            cout << int( y[ l++ ] ) << "\n";
        }
        cout << "\n";
    }

    cout << "\n";

    l = 0;
    for(int i = 0; i < K; ++i)
    {
        for( int j = 0 ; j < N ; ++j ) cout << int( y[ l++ ] ) << " ";
        cout << "\n";
    }

    cout << "\nДобавим в данные шум, чтобы усложнить задачу:\n";

    //# Добавим в данные шум, чтобы усложнить задачу.
    //X[:, 0] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
    //X[:, 1] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
    Noise2D( X );

    l = 0;
    for(int i = 0; i < K; ++i)
    {
        for( int j = 0 ; j < N ; ++j )
        {
            cout.width( 15 );
            cout.setf( ios::fixed | ios::right );
            cout.precision( 8 );
            cout << X[ l ].x << "\t";
            cout.width( 15 );
            cout.setf( ios::fixed | ios::right );
            cout.precision( 8 );
            cout << X[ l ].y << "\t";
            cout.width( 5 );
            cout.setf( ios::fixed | ios::right );
            cout << int( y[ l++ ] ) << "\n";
        }
        cout << "\n";
    }

}

//  Функция создает последовательность данных из  num  точек,
//  равномерно расположенных на числовой прямой
//  в заданном интервале: [start, stop]
//
//  numpy.linspace(start, stop, num, endpoint)
// 
//  start - начало последовательности
//  stop  - конец последовательности
//  num   - количество данных в выборке,
//          включая последнюю точку
//
//  Return: последовательность данных
//
static vector< double >  linspace( const int  start, const int  stop, const int  num )
{
    assert( stop >= start );
    assert( num > 1 );
    vector< double >  t( num );
    const double  delta{ double((int)(stop - start)) / double((int)(num - 1)) };
    for(int i = 0; i < num; ++i )
    {
        t[ i ] = double( start ) + delta * i;
    }
    return t;
}

//  Сложение +
//
//  v1 - 1-ый вектор
//  v2 - 2-ой вектор
//
//  Return: v1 + v2
//
static vector< double >  add( const vector< double >&  v1, const vector< double >&  v2 )
{
    assert( v1.size() == v2.size() );
    vector< double >  res( v1.size() );
    for(auto i = 0; i < v1.size(); ++i)
    {
        res[ i ] = v1[ i ] + v2[ i ];
    }
    return  res;
}

//  Создает массив и заполняет его случайными значениями в
//  соответствии со стандартным нормальным распределением.
//                  standard normal distribution. 
//
//  np.random.randn(N)
//
//  N - кол-во
//
static vector< double >  random_randn(const int N)
{
    vector< double >  v( N, 0 );

    // uncomment to use a non-deterministic seed
    //random_device gen;
    //random_device  rd;
    //mt19937 gen(rd());
    mt19937 gen(1701);
    normal_distribution<> distr( 0, 1 );

    // Средние значение (мат. ожидание)
    //cout << "m() = " << fixed << setw(11) << setprecision(10) << distr.mean() << '\n';
    // Дисперсия (стандартное отклонение)
    //cout << "s() = " << fixed << setw(11) << setprecision(10) << distr.stddev() << '\n';

    // 
    for( auto&  val : v )
    {
        val = distr( gen ) * 0.2; //# theta
        //val = distr( gen );
    }
    return  v;
}

//  Функция, которая генерирует датасет "Игрушка дьявола"
//  из N точек и K классов точек в 2-мерном пространстве.
//
//  N - кол-во точек
//  K - классов точек
//  X - координаты точек
//  y - "принадлежность" точек
//
//  Return: 0 - Ok
//
int  devil2D(const int  N, const int  K, vector< Point2D >& X, vector< unsigned char >& y)
{
    X.resize((static_cast<std::vector<Point2D, std::allocator<Point2D>>::size_type>(N)) * K);
    y.resize(static_cast<std::vector<unsigned char, std::allocator<unsigned char>>::size_type>(N) * K);

    for( auto&  val : X )  val = {0, 0};
    for( auto&  val : y )  val = 0;

    // r = np.linspace(0.0, 1, N)
    // r[ 0 ] = 0.0, r[ 1 ], ... r[ N - 1 ] = 1.0
    const double  delta = 1./(N - 1);

    // По классам
    // for j in range(K):
    for(int j = 0; j < K; ++j)
    {
        // Функция создает последовательность данных из N точек,
        // равномерно расположенных на числовой прямой
        // в заданном интервале: [j * 4, (j + 1) * 4]
        //t = np.linspace( j * 4, (j + 1) * 4, N ) + np.random.randn(N) * 0.2 # theta
        vector< double >  t = linspace( j * 4, (j + 1) * 4, N );
        t = add( t, random_randn(N) );
        int  i{0};
        // По точкам
        // ix = range(N * j, N * (j + 1))
        for( int ix = N * j ; ix < N * (j + 1) ; ++ix )
        {
            //           r                               r
            X[ ix ] = { (delta * i) * sin( t[ i ]), (delta * i) * cos( t[ i ])};  ++i;
            y[ ix ] = j;
        }
    }

    return 0; //Ok
}

//# Добавим в данные шум, чтобы усложнить задачу.
//X[:, 0] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
//X[:, 1] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
//
int  Noise2D(vector< Point2D >&  X)
{
    // uncomment to use a non-deterministic seed
    //random_device gen;
    //random_device  rd;
    //mt19937 gen(rd());
    mt19937  gen(1701);
    normal_distribution<>  distr( 0, 0.15 );

    //// Средние значение (мат. ожидание)
    //cout << "m() = " << fixed << setw(11) << setprecision(10) << distr.mean() << '\n';
    //// Дисперсия (стандартное отклонение)
    //cout << "s() = " << fixed << setw(11) << setprecision(10) << distr.stddev() << '\n';

    // 
    for( auto&  val : X )
    {
        val.x = distr( gen );
    }
    // 
    for( auto&  val : X )
    {
        val.y = distr( gen );
    }

    return 0; //Ok
}
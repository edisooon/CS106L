template <typename T>
class grid
{
public:
  /* Constructors, desctructors. */
  grid();
  grid(int rows, int cols);

  /* Resizing operations */
  void clear();                    // Empty the grid
  void resize(int rows, int cols); // Resize the grid

  /* Query operations */
  int numRows() const;
  int numCols() const;
  bool empty() const;
  int size() const;

  /* Element access. */
  T &getAt(int row, int col);
  const T &getAt(int row, int col) const;

private:
  vector<T> elems;
  int rows;
  int cols;
};

template <typename T>
grid<T>::grid() : rows(0), cols(0)
{
}

template <typename T>
grid<T>::grid(int rows, int cols) : elems(rows * cols), rows(rows), cols(cols)
{
}

template <typename T>
void grid<T>::clear()
{
  resize(0, 0);
}

template <typename T>
void grid<T>::resize(int rows, int cols)
{
  elems.assign(rows * cols, ElemType());

  this->rows = rows;
  this->cols = cols;
}

template <typename T>
int grid<T>::numRows() const
{
  return rows;
}

template <typename T>
int grid<T>::numCols() const
{
  return cols;
}

template <typename T>
bool grid<T>::empty() const
{
  return size() == 0;
}

template <typename T>
int grid<T>::size() const
{
  return numRows() * numCols();
}

template <typename T>
T &grid<T>::getAt(int row, int col)
{
  return elems[col + row * cols];
}

template <typename T>
const T &grid<T>::getAt(int row, int col) const
{
  return elems[col + row * cols];
}
namespace helper
{
template <class KeyClass, class ValueClass, int Size>
class CompileTimeMap
{
 public:
  CompileTimeMap() = default;
  ~CompileTimeMap() = default;

 public:
  struct KeyValuePair
  {
    KeyClass key;
    ValueClass value;
  };

  constexpr ValueClass operator[](KeyClass key) const { return Get(key); }

 private:
  constexpr ValueClass Get(KeyClass key, int i = 0) const
  {
    return i == Size             ? KeyNotFound()
           : pairs[i].key == key ? pairs[i].value
                                 : Get(key, i + 1);
  }

  static ValueClass KeyNotFound() // not constexpr
  {
    return {};
  }

 public:
  KeyValuePair pairs[Size];
}; // CompileTimeMap
} // namespace helper
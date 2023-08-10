#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), buffer_queue(),
  bytes_written(0), bytes_read(0),is_error( false), is_over(false){}

void Writer::push(string data) {
  // Your code here.
  size_t size = min(data.size(), capacity_ - buffer_queue.size());
  data = data.substr(0, size);
  for (const auto &c : data) {
    buffer_queue.push_back(c);
  }
  bytes_written += size;
}
void Writer::close()
{
  is_over = true;
}

void Writer::set_error()
{
  is_error = true;
}

bool Writer::is_closed() const
{
  return is_over;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_queue.size();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_written;
}

string_view Reader::peek() const
{
  return string_view(&buffer_queue.front(), 1);
}

bool Reader::is_finished() const
{
  return is_over && buffer_queue.empty();
}

bool Reader::has_error() const
{
  return is_error;
}

void Reader::pop( uint64_t len )
{
  size_t size = min(len, buffer_queue.size());
  buffer_queue.erase(buffer_queue.begin(), buffer_queue.begin() + size);
  bytes_read += size;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_queue.size();
}

uint64_t Reader::bytes_popped() const
{
  return bytes_read;
}

//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2021
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/utils/common.h"
#include "td/utils/StringBuilder.h"

#include <ctime>
#include <functional>
#include <type_traits>

namespace td {

class ChatId {
  int32 id = 0;
  int64 time_ = INT64_MAX;

 public:
  explicit ChatId() {
    set_time();
  };

  explicit ChatId(int32 chat_id) : id(chat_id) {
    set_time();
  }
  template <class T, typename = std::enable_if_t<std::is_convertible<T, int32>::value>>
  ChatId(T chat_id) = delete;

  bool is_valid() const {
    return id > 0;
  }

  int32 get() const {
    return id;
  }

  void set_time() {
    time_ = std::time(nullptr);
  }

  int64 get_time() const {
    return time_;
  }

  void reset_time() {
    time_ = INT64_MAX;
  }

  bool operator==(const ChatId &other) const {
    return id == other.id;
  }

  bool operator!=(const ChatId &other) const {
    return id != other.id;
  }

  template <class StorerT>
  void store(StorerT &storer) const {
    storer.store_int(id);
  }

  template <class ParserT>
  void parse(ParserT &parser) {
    id = parser.fetch_int();
  }
};

struct ChatIdHash {
  std::size_t operator()(ChatId chat_id) const {
    return std::hash<int32>()(chat_id.get());
  }
};

inline StringBuilder &operator<<(StringBuilder &string_builder, ChatId chat_id) {
  return string_builder << "basic group " << chat_id.get();
}

}  // namespace td

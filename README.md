# 🧑‍🤝‍🧑 Social Network Console Application in C++

This is a **console-based social network simulation** written in **C++**. It allows users to create profiles, manage friendships, and receive friend recommendations based on **mutual friends** or **shared interests**. The app also includes functionality to search users by city and display mutual connections.

---

## 🚀 Features

- **Add User**: Create a new user with name, age, city, and interests.
- **Add Friendship**: Link two users as friends (bi-directional).
- **Remove Friendship**: Delete a friendship between two users.
- **Show Profile**: Display details like name, age, city, interests, and friends.
- **Recommend by Mutual Friends**: Suggest friends based on the number of shared connections.
- **Recommend by Interests**: Suggest friends with similar hobbies/interests.
- **Show Mutual Friends**: List mutual friends between two users.
- **List Users by City**: View all users from a specific city.

---

## 📁 File Structure

```

.
├── main.cpp      # Main source code file
└── README.md     # Project description and instructions

````

---

## 🛠️ Requirements

- C++11 or later
- A C++ compiler (like `g++`)

---

## 🧑‍💻 How to Compile and Run

### 🔹 Compile

```bash
g++ -std=c++11 -o FriendshipRecommendation.cpp
````

### 🔹 Run

```bash
./FriendshipRecommendation
```

---

## 📋 Sample Menu

```
--- Social Network Menu ---
1. Add User
2. Add Friendship
3. Remove Friendship
4. Show Profile
5. Recommend by Mutual Friends
6. Recommend by Interests
7. Show Mutual Friends
8. List Users by City
9. Exit
Choice:
```

---

## 🧹 Future Improvements

* Save and load data from file
* Add GUI (e.g., using Qt or web-based frontend)
* Add profile picture (using file paths)
* Improve recommendation algorithms with weights

---

## 📄 License

This project is licensed for educational purposes.

---

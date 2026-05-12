import tkinter as tk
from tkinter import ttk, messagebox
from sequence_wrapper import MutableArraySequence

class App:
    def __init__(self, root):
        self.root = root
        self.root.title("MutableArraySequence Tester")
        self.root.geometry("800x600")
        
        self.seq = MutableArraySequence()
        self._build_ui()
        self.update_display()
    
    def _build_ui(self):
        main = ttk.Frame(self.root, padding="10")
        main.grid(row=0, column=0, sticky="nsew")
        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1)
        main.grid_rowconfigure(0, weight=1)
        for col in range(4):
            main.grid_columnconfigure(col, weight=1)
        
        self.display = tk.Text(main, height=10, font=("Courier", 12))
        self.display.grid(row=0, column=0, columnspan=4, sticky="nsew", pady=5)
        
        ttk.Label(main, text="Value:").grid(row=1, column=0, sticky="w", pady=5)
        self.val_entry = ttk.Entry(main, width=10)
        self.val_entry.grid(row=1, column=1, sticky="w", pady=5)
        
        ttk.Label(main, text="Index:").grid(row=2, column=0, sticky="w", pady=5)
        self.idx_entry = ttk.Entry(main, width=10)
        self.idx_entry.grid(row=2, column=1, sticky="w", pady=5)
        
        ttk.Button(main, text="Append", command=self._append).grid(row=3, column=0, pady=5, padx=5)
        ttk.Button(main, text="Prepend", command=self._prepend).grid(row=3, column=1, pady=5, padx=5)
        ttk.Button(main, text="Insert At", command=self._insert).grid(row=3, column=2, pady=5, padx=5)
        ttk.Button(main, text="Get", command=self._get).grid(row=4, column=0, pady=5, padx=5)
        ttk.Button(main, text="Get First", command=self._get_first).grid(row=4, column=1, pady=5, padx=5)
        ttk.Button(main, text="Get Last", command=self._get_last).grid(row=4, column=2, pady=5, padx=5)
        ttk.Button(main, text="Clear", command=self._clear).grid(row=4, column=3, pady=5, padx=5)
    
    def update_display(self):
        self.display.delete(1.0, tk.END)
        self.display.insert(1.0, self.seq.to_string())
        self.display.insert(tk.END, f"\n\nLength: {self.seq.get_length()}")
    
    def _get_int(self, entry):
        try:
            return int(entry.get())
        except ValueError:
            messagebox.showerror("Error", "Please enter a valid integer")
            return None
    
    def _append(self):
        v = self._get_int(self.val_entry)
        if v is None: return
        try:
            self.seq.append(v)
            self.val_entry.delete(0, tk.END)
            self.update_display()
        except Exception as e:
            messagebox.showerror("Error", str(e))
    
    def _prepend(self):
        v = self._get_int(self.val_entry)
        if v is None: return
        try:
            self.seq.prepend(v)
            self.val_entry.delete(0, tk.END)
            self.update_display()
        except Exception as e:
            messagebox.showerror("Error", str(e))
    
    def _insert(self):
        v = self._get_int(self.val_entry)
        i = self._get_int(self.idx_entry)
        if v is None or i is None:
            return
        try:
            self.seq.insert_at(i, v)
            self.val_entry.delete(0, tk.END)
            self.idx_entry.delete(0, tk.END)
            self.update_display()
        except Exception as e:
            messagebox.showerror("Error", str(e))
    
    def _get(self):
        i = self._get_int(self.idx_entry)
        if i is None: return
        try:
            val = self.seq.get(i)
            messagebox.showinfo("Get", f"Value at index {i}: {val}")
        except Exception as e:
            messagebox.showerror("Error", str(e))
    
    def _get_first(self):
        try:
            val = self.seq.get_first()
            messagebox.showinfo("Get First", f"First value: {val}")
        except Exception as e:
            messagebox.showerror("Error", str(e))
    
    def _get_last(self):
        try:
            val = self.seq.get_last()
            messagebox.showinfo("Get Last", f"Last value: {val}")
        except Exception as e:
            messagebox.showerror("Error", str(e))
    
    def _clear(self):
        try:
            self.seq.clear()
            self.update_display()
        except Exception as e:
            messagebox.showerror("Error", str(e))

if __name__ == "__main__":
    root = tk.Tk()
    App(root)
    root.mainloop()
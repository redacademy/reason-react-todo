type state = {
  items: list(TodoModel.item),
  inputText: string,
};

type action =
  | InputText(string)
  | Toggle(int)
  | DeleteAll
  | RemoveItem(int)
  | Submit;

let component = ReasonReact.reducerComponent("TodoLists");

let str = ReasonReact.string;

let make = _children => {
  let handleSubmit = state => {
    let newId: int = List.length(state.items);
    let newItem: TodoModel.item = {
      id: newId,
      title: state.inputText,
      completed: false,
    };
    let newList = [newItem, ...state.items];
    ReasonReact.Update({items: newList, inputText: ""});
  };
  {
    ...component,
    initialState: () => {
      items: [{id: 0, title: "milk", completed: false}],
      inputText: "",
    },
    reducer: action =>
      switch (action) {
      | InputText(newText) => (
          state => ReasonReact.Update({...state, inputText: newText})
        )
      | Toggle(id) => state => ReasonReact.Update({...state, items: List.map((item: TodoModel.item) => item.id == id ? {...item, TodoModel.completed: ! TodoModel.(item.completed)} :item , state.items)})
      | RemoveItem(id) => state => ReasonReact.Update({...state, items: List.filter((item: TodoModel.item) => item.id !== id, state.items)})
      | Submit => (state => handleSubmit(state))
      | DeleteAll => (state => ReasonReact.Update({...state, items: []}))
      },
    render: self => {
      let {items, inputText} = self.state;
      /* Js.log(inputText); */
      let numItems = List.length(items);
      let word = numItems === 1 ? " item" : " items";
      <div className="app">
        <AddTodo submit={(_) => self.send(Submit)} value={inputText} onInputText={(text) => self.send(InputText(text))} />
        <div className="list">

          (
            ReasonReact.array(
              Array.of_list(
                List.map(
                  (item: TodoModel.item) =>
                    <TodoItem key=(string_of_int(item.id)) item onRemove={(id) =>self.send(RemoveItem(id))} onToggle={(id) =>self.send(Toggle(id))}/>,
                  items,
                ),
              ),
            )
          )
        </div>
        <div className="footer">
          <button onClick=((_) => self.send(DeleteAll))>
            (str("Delete All"))
          </button>
          <p> (str(string_of_int(numItems) ++ word)) </p>
        </div>
      </div>;
    },
  };
};
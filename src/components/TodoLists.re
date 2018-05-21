type item = {
    title: string,
    completed: bool
}

type state = {
    items: list(item)
}

let component = ReasonReact.reducerComponent("TodoLists");

let ste = ReasonReact.stringToElement;

let make = (children) => {
    ...component,
    initialState: () => {
        items: [
            {title: "milk", completed: false}
        ]
    },
    reducer: ((), _) => ReasonReact.NoUpdate,
    render: ({state: {items}}) => {
        let numItems = List.length(items);
        let word = (numItems === 1) ? " item" : "items";
        <div className="app">
          <div className="footer">
            (ste(string_of_int(numItems) ++ word))
          </div>
        </div>
      }

}